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

#include "LODTileBuilder.h"
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>

namespace CDB2OSG {
    
    LODTileBuilder::LODTileBuilder() {
        this->subsamplingEnabled = false;
    }
    
    osg::LOD *LODTileBuilder::getLodNode() {
        lodNode = new osg::LOD();
        return lodNode;
    }
    
    void LODTileBuilder::setupMoreDetailedChildForRange(double min, double max, CDB::LodTile::List lodTilesToLoad) {
        LODTileBuilder *moreDetailedTilesBuilder = new LODTileBuilder();
        moreDetailedTilesBuilder->database = database;
        moreDetailedTilesBuilder->terrain = terrain;
        moreDetailedTilesBuilder->lodPolicy = lodPolicy;
        moreDetailedTilesBuilder->nextTiles = nextTiles;
        moreDetailedTilesBuilder->subsamplingEnabled = subsamplingEnabled;
        
        osg::ref_ptr<osg::Group> group = new osg::Group();
        for (unsigned int i = 0; i < lodTilesToLoad.size(); i++) {
            CDB::LodTile *lodTile = lodTilesToLoad.at(i);
            moreDetailedTilesBuilder->setLodTile(lodTile);
            
            osg::ref_ptr<osg::Node> tile = moreDetailedTilesBuilder->build();
            group->addChild(tile);
        }
        
        lodNode->addChild(group, min, max);
    }
    
    LODTileBuilder::~LODTileBuilder() {
        
    }
    
}
