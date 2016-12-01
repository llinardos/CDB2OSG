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

#include "PrimaryImageryLinker.h"
#include <CDB2OSG/Functions.h>

namespace CDB2OSG {
    
    PrimaryImageryLinker::PrimaryImageryLinker(int layerIndex) {
        this->layerIndex = layerIndex;
    }
    
    void PrimaryImageryLinker::setImageFromCDB(osg::Image *image) {
        this->image = image;
    }
    
    void PrimaryImageryLinker::setLodTileFromCDB(CDB::LodTile *lodTile) {
        this->lodTile = lodTile;
    }
    
    void PrimaryImageryLinker::setOsgTerrainTile(osgTerrain::TerrainTile *terrainTile) {
        this->terrainTile = terrainTile;
    }
    
    void PrimaryImageryLinker::link() {
        osgTerrain::Locator *osgLocator = getOsgLocatorForCDBLodTile(lodTile);
        
        osg::ref_ptr<osgTerrain::Layer> imageryLayer = new osgTerrain::ImageLayer(image);
        imageryLayer->setLocator(osgLocator);
        terrainTile->setColorLayer(layerIndex, imageryLayer);
    }
    
}
