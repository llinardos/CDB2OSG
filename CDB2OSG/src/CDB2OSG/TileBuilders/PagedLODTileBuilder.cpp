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

#include "PagedLODTileBuilder.h"
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>

namespace CDB2OSG {
    
    PagedLODTileBuilder::ReaderCallback::ReaderCallback() {
        tileBuilder = NULL;
    }
    
    PagedLODTileBuilder::ReaderCallback::~ReaderCallback() {
        
    }
    
    void PagedLODTileBuilder::ReaderCallback::setTileBuilder(CDB2OSG::TileBuilder *tileBuilder) {
        this->tileBuilder = tileBuilder;
    }
    
    osgDB::ReaderWriter::ReadResult PagedLODTileBuilder::ReaderCallback::readNode(const std::string &filename,
                                                                                  const osgDB::Options *options) {
        osg::ref_ptr<osg::Group> group = new osg::Group();
        CDB::LodTile::List *lodTiles = (CDB::LodTile::List *) (options->getPluginData(PagedLOD::LodTilesToLoadKeyOnOptionsPluginData));
        for (unsigned int i = 0; i < lodTiles->size(); i++) {
            CDB::LodTile *lodTile = lodTiles->at(i);
            tileBuilder->setLodTile(lodTile);
            
            osg::ref_ptr<osg::Node> tile = tileBuilder->build();
            group->addChild(tile);
        }
        
        osgDB::ReaderWriter::ReadResult rr;
        if (group.valid()) {
            rr = osgDB::ReaderWriter::ReadResult(group);
        } else {
            rr = osgDB::ReaderWriter::ReadResult(osgDB::ReaderWriter::ReadResult::ERROR_IN_READING_FILE);
        }
        return rr;
    }
    
    PagedLODTileBuilder::PagedLODTileBuilder() {
        this->subsamplingEnabled = false;
    }

    osg::LOD *PagedLODTileBuilder::getLodNode() {
        pLod = new CDB2OSG::PagedLOD();
        return pLod;
    }
    
    void PagedLODTileBuilder::setupMoreDetailedChildForRange(double min, double max, CDB::LodTile::List lodTilesToLoad) {
        PagedLODTileBuilder *moreDetailedTilesBuilder = new PagedLODTileBuilder();
        moreDetailedTilesBuilder->database = database;
        moreDetailedTilesBuilder->terrain = terrain;
        moreDetailedTilesBuilder->lodPolicy = lodPolicy;
        moreDetailedTilesBuilder->nextTiles = nextTiles;
        moreDetailedTilesBuilder->subsamplingEnabled = subsamplingEnabled;
        
        osg::ref_ptr<PagedLODTileBuilder::ReaderCallback> cdbReaderCallback = new PagedLODTileBuilder::ReaderCallback();
        cdbReaderCallback->setTileBuilder(moreDetailedTilesBuilder);

        osg::ref_ptr<osgDB::Options> pLodOptions = dynamic_cast<osgDB::Options*>(pLod->getDatabaseOptions());
        pLodOptions->setReadFileCallback(cdbReaderCallback);
        
        pLod->addLodTilesToLoadForRange(lodTilesToLoad, min, max);
    }
    
    PagedLODTileBuilder::~PagedLODTileBuilder() {
        
    }
    
}
