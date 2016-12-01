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

#include "PrimaryElevationLinker.h"
#include <CDB2OSG/Functions.h>

namespace CDB2OSG {
    
    PrimaryElevationLinker::PrimaryElevationLinker() {
    	this->skirtHeight = 0;
    }
    
    void PrimaryElevationLinker::setHeightFieldFromCDB(osg::HeightField *heightfield) {
        this->heightfield = heightfield;
    }
    
    void PrimaryElevationLinker::setLodTileFromCDB(CDB::LodTile *lodTile) {
        this->lodTile = lodTile;
    }
    
    void PrimaryElevationLinker::setOsgTerrainTile(osgTerrain::TerrainTile *terrainTile) {
        this->terrainTile = terrainTile;
    }
    
    void PrimaryElevationLinker::setSkirtHeight(float height) {
        skirtHeight = height;
    }
    
    void PrimaryElevationLinker::link() {
        //            Latitude southLatitude, northLatitude;
        //            Longitude westLongitude, eastLongitude;
        //
        //            southLatitude = Latitude(heightField->getOrigin().y());
        //            westLongitude = Longitude(heightField->getOrigin().x());
        //
        //            northLatitude = Latitude(heightField->getOrigin().y() + heightField->getNumColumns() * heightField->getXInterval());
        //            eastLongitude = Longitude(heightField->getOrigin().x() + heightField->getNumRows() * heightField->getYInterval());
        //
        //            osg::ref_ptr<osgTerrain::Locator> locatorFromCDB = new osgTerrain::Locator();
        //            locatorFromCDB->setCoordinateSystemType(osgTerrain::Locator::GEOCENTRIC);
        //            locatorFromCDB->setTransformAsExtents(
        //                                                  osg::DegreesToRadians(westLongitude.getValue()),
        //                                                  osg::DegreesToRadians(southLatitude.getValue()),
        //                                                  osg::DegreesToRadians(eastLongitude.getValue()),
        //                                                  osg::DegreesToRadians(northLatitude.getValue()));
        
        osgTerrain::Locator *osgLocator = getOsgLocatorForCDBLodTile(lodTile);
        osgTerrain::TileID osgTileId = getOsgTileIdForCDBLodTile(lodTile);
        
        heightfield->setSkirtHeight(skirtHeight);
        
        osgTerrain::HeightFieldLayer *elevationLayer = new osgTerrain::HeightFieldLayer(heightfield);
        elevationLayer->setLocator(osgLocator);
        terrainTile->setElevationLayer(elevationLayer);
        terrainTile->setTileID(osgTileId);
        
    }
    
};
