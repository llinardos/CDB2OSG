/* Copyright (C) 2014-2016 Leandro Linardos, Buenos Aires, Argentina
 *
 * This file is part of CDB2OSG.
 *
 * CDB2OSG is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 */

#include "PagedLOD.h"

namespace CDB2OSG {
    
    const std::string PagedLOD::LodTilesToLoadKeyOnOptionsPluginData = "LodTilesToLoad";
    
    PagedLOD::PagedLOD() : osg::PagedLOD() {
        osg::ref_ptr<osgDB::Options> options = new osgDB::Options();
        this->setDatabaseOptions(options);
    }
    
    PagedLOD::PagedLOD(const PagedLOD &plod, const osg::CopyOp &copyop) :
    osg::PagedLOD(plod, copyop) {
    }
    
    PagedLOD::PagedLOD(PagedLOD &plod, const osg::CopyOp &copyop) :
    osg::PagedLOD(plod, copyop) {
    }
    
    CDB::LodTile::List PagedLOD::getLodTilesToLoad() {
        return lodTilesToLoad;
    }
    
    void PagedLOD::addLodTilesToLoadForRange(CDB::LodTile::List lodTiles, float min, float max) {
        lodTilesToLoad = lodTiles;
        
        unsigned int newChildNumber = _perRangeDataList.size();
        expandPerRangeDataTo(newChildNumber);
        this->setRange(newChildNumber, min, max);
        
        osg::ref_ptr<osgDB::Options> options = dynamic_cast<osgDB::Options *>(_databaseOptions.get());
        options->setPluginData(PagedLOD::LodTilesToLoadKeyOnOptionsPluginData, &lodTilesToLoad);
    }
    
    unsigned int PagedLOD::getNumTiles() const {
        return _perRangeDataList.size();
    }
    
    void PagedLOD::traverse(osg::NodeVisitor &nv) {
        this->setCenterMode(CDB2OSG::PagedLOD::USE_BOUNDING_SPHERE_CENTER);
        
        // set the frame number of the traversal so that external nodes can find out how active this
        // node is.
        if (nv.getFrameStamp() &&
            nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR) {
            setFrameNumberOfLastTraversal(nv.getFrameStamp()->getFrameNumber());
        }
        
        double timeStamp = nv.getFrameStamp() ? nv.getFrameStamp()->getReferenceTime() : 0.0;
        unsigned int frameNumber = nv.getFrameStamp() ? nv.getFrameStamp()->getFrameNumber() : 0;
        bool updateTimeStamp = nv.getVisitorType() == osg::NodeVisitor::CULL_VISITOR;
        
        switch (nv.getTraversalMode()) {
            case (osg::NodeVisitor::TRAVERSE_ALL_CHILDREN):
                std::for_each(_children.begin(), _children.end(), osg::NodeAcceptOp(nv));
                break;
            case (osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN): {
                float required_range = 0;
                if (_rangeMode == DISTANCE_FROM_EYE_POINT) {
                    required_range = nv.getDistanceToViewPoint(getCenter(), true);
                } else {
                    osg::CullStack *cullStack = dynamic_cast<osg::CullStack *>(&nv);
                    if (cullStack && cullStack->getLODScale() > 0.0f) {
                        required_range = cullStack->clampedPixelSize(getBound()) / cullStack->getLODScale();
                    } else {
                        // fallback to selecting the highest res tile by
                        // finding out the max range
                        for (unsigned int i = 0; i < _rangeList.size(); ++i) {
                            required_range = osg::maximum(required_range, _rangeList[i].first);
                        }
                    }
                }
                
                
                int lastChildTraversed = -1;
                bool needToLoadChild = false;
                for (unsigned int i=0; i<_rangeList.size(); ++i)
                {
                    if (_rangeList[i].first<=required_range && required_range<_rangeList[i].second)
                    {
                        if (i<_children.size())
                        {
                            if (updateTimeStamp) _perRangeDataList[i]._timeStamp=timeStamp;
                            
                            _children[i]->accept(nv);
                            lastChildTraversed = (int)i;
                        }
                        else
                        {
                            needToLoadChild = true;
                        }
                    }
                }
                
                if (needToLoadChild) {
                    unsigned int numChildren = _children.size();
                    
                    // select the last valid child.
                    if (numChildren > 0 && ((int) numChildren - 1) != lastChildTraversed) {
                        if (updateTimeStamp) {
                            _perRangeDataList[numChildren - 1]._timeStamp = timeStamp;
                            _perRangeDataList[numChildren - 1]._frameNumber = frameNumber;
                        }
                        _children[numChildren - 1]->accept(nv);
                    }
                    
                    // now request the loading of the next unloaded child.
                    if (!_disableExternalChildrenPaging &&
                        nv.getDatabaseRequestHandler() &&
                        numChildren < _perRangeDataList.size()) {
                        // compute priority from where abouts in the required range the distance falls.
                        float priority = (_rangeList[numChildren].second - required_range) /
                        (_rangeList[numChildren].second - _rangeList[numChildren].first);
                        
                        // invert priority for PIXEL_SIZE_ON_SCREEN mode
                        if (_rangeMode == PIXEL_SIZE_ON_SCREEN) {
                            priority = -priority;
                        }
                        
                        // modify the priority according to the child's priority offset and scale.
                        priority = _perRangeDataList[numChildren]._priorityOffset +
                        priority * _perRangeDataList[numChildren]._priorityScale;
                        
                        
                        // TODO: fix this
                        const void *address = static_cast<const void *>(this);
                        std::stringstream ss;
                        ss << address;
                        
                        if (_databasePath.empty()) {
                            nv.getDatabaseRequestHandler()->requestNodeFile(ss.str(), nv.getNodePath(), priority,
                                                                            nv.getFrameStamp(),
                                                                            _perRangeDataList[numChildren]._databaseRequest,
                                                                            _databaseOptions.get());
                        } else {
                            // prepend the databasePath to the child's filename.
                            nv.getDatabaseRequestHandler()->requestNodeFile(ss.str(), nv.getNodePath(), priority,
                                                                            nv.getFrameStamp(),
                                                                            _perRangeDataList[numChildren]._databaseRequest,
                                                                            _databaseOptions.get());
                        }
                    }
                    
                }
                
                
                break;
            }
            default:
                break;
        }
    }
    
    PagedLOD::~PagedLOD() { }
    
}
