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

#include "Functions.h"
#include <CDB/Model/Model.h>

namespace CDB2OSG {
    
    osgTerrain::TileID getOsgTileIdForCDBLodTile(CDB::LodTile *lodTile) {
        int lod = lodTile->getLevelOfDetail().getValue();
        
        int xGeocellComponent =
        (lodTile->getGeocell().getLatitude().getValue() + 90) * lodTile->getLevelOfDetail().getNumberOfDivisions();
        int xTileComponent = lodTile->getURef().getValue();
        int x = xGeocellComponent + xTileComponent;
        
        int yGeocellComponent = (lodTile->getGeocell().getLongitude().getValue() + 180) *
        lodTile->getLevelOfDetail().getNumberOfDivisions();
        int yTileComponent = lodTile->getRRef().getValue();
        int y = yGeocellComponent + yTileComponent;
        
        return osgTerrain::TileID(lod, x, y);
    }
    
    osgTerrain::Locator *getOsgLocatorForCDBLodTile(CDB::LodTile *lodTile) {
        CDB::Latitude southLatitude, northLatitude;
        CDB::Longitude westLongitude, eastLongitude;
        lodTile->coordinates(southLatitude, northLatitude, eastLongitude, westLongitude);
        
        osg::ref_ptr <osgTerrain::Locator> locator = new osgTerrain::Locator();
        locator->setCoordinateSystemType(osgTerrain::Locator::GEOCENTRIC);
        locator->setTransformAsExtents(
                                       osg::DegreesToRadians(westLongitude.getValue()),
                                       osg::DegreesToRadians(southLatitude.getValue()),
                                       osg::DegreesToRadians(eastLongitude.getValue()),
                                       osg::DegreesToRadians(northLatitude.getValue()));
        
        return locator.release();
    }
    
};
