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

#include "ProgressiveTileBuilder.h"
#include <CDB/ResourceAccesors/ImageResourceAccesor.h>
#include <CDB2OSG/TileBuilders/BasicTileBuilder.h>

namespace CDB2OSG {
        
    void ProgressiveTileBuilder::setLodPolicy(LODPolicy *lodPolicy) {
        this->lodPolicy = lodPolicy;
    }
    
    void ProgressiveTileBuilder::setNextTiles(NextTiles *nextTiles) {
        this->nextTiles = nextTiles;
    }
    
    void ProgressiveTileBuilder::enableElevationSubsampling(bool enable) {
        this->subsamplingEnabled = enable;
    }
    
    osg::Node *ProgressiveTileBuilder::build() {
        if (!this->nextTiles.valid()) {
            this->nextTiles = new NextTilesNone();
        }
        
        // First tile
        CDB2OSG::BasicTileBuilder *tileBuilder = new CDB2OSG::BasicTileBuilder();
        tileBuilder->enableElevationSubsampling(subsamplingEnabled);
        tileBuilder->setDatabase(database);
        tileBuilder->setLodTile(lodTile);
        tileBuilder->setTerrain(terrain);
        
        osg::ref_ptr<osg::Node> tile = tileBuilder->build();
        
        CDB::LodTile::List nextLevelLodTiles = this->nextTiles->forLodTile(lodTile);
        if (nextLevelLodTiles.empty()) {
            return tile.release();
        } else {
            // The tile is a component in a LOD node, and this subgraph is returned as result
            osg::ref_ptr<osg::LOD> lodNode = this->getLodNode();
            
            float min, max;
            lodPolicy->rangeLimitsForLOD(lodTile->getLevelOfDetail(), min, max);
            lodNode->addChild(tile, min, FLT_MAX);
            setupMoreDetailedChildForRange(0, min, nextLevelLodTiles);
            
            return lodNode.release();
        }
    }
    
};
