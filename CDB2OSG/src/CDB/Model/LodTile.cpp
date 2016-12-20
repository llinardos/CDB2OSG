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

#include <CDB/Model/LodTile.h>

namespace CDB {
    
    LodTile::LodTile(
                     Geocell geocell,
                     LOD levelOfDetail,
                     URef upIndex,
                     RRef rightIndex) :
    geocell(geocell),
    levelOfDetail(levelOfDetail),
    uRef(upIndex),
    rRef(rightIndex) {
        
    }
    
    LodTile::LodTile(
                     Latitude geoCellLatitude,
                     Longitude geoCellLongitude,
                     LOD levelOfDetailValue,
                     URef upIndex,
                     RRef rightIndex) :
    geocell(geoCellLatitude, geoCellLongitude),
    levelOfDetail(levelOfDetailValue),
    uRef(upIndex),
    rRef(rightIndex) {
        
    }
    
    LodTile::LodTile(const LodTile &otherLodTile) :
    geocell(otherLodTile.geocell),
    levelOfDetail(otherLodTile.levelOfDetail),
    uRef(otherLodTile.uRef),
    rRef(otherLodTile.rRef) {
        
    }
    
    LodTile &LodTile::operator=(const LodTile &otherLodTile) {
        geocell = otherLodTile.geocell;
        levelOfDetail = otherLodTile.levelOfDetail;
        uRef = otherLodTile.uRef;
        rRef = otherLodTile.rRef;
        return *this;
    }
    
    bool LodTile::operator==(const LodTile &otherLodTile) const {
        return geocell == otherLodTile.geocell &&
        levelOfDetail == otherLodTile.levelOfDetail &&
        uRef == otherLodTile.uRef &&
        rRef == otherLodTile.rRef;
    }
    
    
    const Geocell &LodTile::getGeocell() const {
        return geocell;
    }
    
    const LOD &LodTile::getLevelOfDetail() const {
        return levelOfDetail;
    }
    
    const URef &LodTile::getURef() const {
        return uRef;
    }
    
    const RRef &LodTile::getRRef() const {
        return rRef;
    }
    
    void LodTile::coordinates(Latitude &southLat,
                              Latitude &northLat,
                              Longitude &eastLon,
                              Longitude &westLon) {
        Zone zone = getGeocell().getZone();
        int latitudeLongitudeRatio = zone.latitudeLongitudeRatio();
        
        double numberOfDivisions = std::max<double>(levelOfDetail.getNumberOfDivisions(), 1.0);
        
        southLat = getGeocell().getLatitude() + Latitude(uRef.getValue() / numberOfDivisions);
        northLat = getGeocell().getLatitude() + Latitude((uRef.getValue() + 1) / numberOfDivisions);
        westLon = getGeocell().getLongitude() + Longitude((rRef.getValue() * latitudeLongitudeRatio) / numberOfDivisions);
        eastLon = getGeocell().getLongitude() + Longitude(((rRef.getValue() + 1) * latitudeLongitudeRatio) / numberOfDivisions);
    }
    
    
    CDB::LodTile::List LodTile::getMoreDetailesLodTiles() {
        CDB::LodTile::List lodTilesList;
        
        CDB::LodTile::List moreDetailedLodTiles;
        if (getLevelOfDetail().getValue() < 0) {
            osg::ref_ptr<CDB::LodTile> lodTile = new CDB::LodTile(
                                                                  geocell,
                                                                  levelOfDetail.getMoreDetailedLOD(),
                                                                  uRef,
                                                                  rRef);
            lodTilesList.push_back(lodTile);
        } else {
            addMoreDetailedLodTilesTo(lodTilesList, 1);
        }
        
        return lodTilesList;
    }
    
    void LodTile::addMoreDetailedLodTilesTo(
                                            CDB::LodTile::List &lodTilesList,
                                            int levelDiff) {
        unsigned int minURef = (unsigned int) (uRef.getValue() * powf(2, levelDiff));
        unsigned int maxURef = (unsigned int) (minURef + powf(2, levelDiff) - 1);
        unsigned int minRRef = (unsigned int) (rRef.getValue() * powf(2, levelDiff));
        unsigned int maxRRef = (unsigned int) (minRRef + powf(2, levelDiff) - 1);
        
        for (unsigned int uRef = minURef; uRef <= maxURef; uRef++) {
            for (unsigned int rRef = minRRef; rRef <= maxRRef; rRef++) {
                osg::ref_ptr<CDB::LodTile> lodTile = new CDB::LodTile(
                                                                      geocell,
                                                                      LOD(levelOfDetail.getValue() + levelDiff),
                                                                      uRef,
                                                                      rRef);
                lodTilesList.push_back(lodTile);
            }
        }
    }
    
    LodTile* LodTile::getLodTileAtLowerLOD() {
        LOD lod = levelOfDetail.getLessDetailedLOD();
        
        if (lod.getValue() <= 0) {
            return new LodTile(LodTile(geocell, lod, URef(0), RRef(0)));
        } else {
            int levelDiff = levelOfDetail.getValue() - lod.getValue();
            
            URef urefAtLowerLOD = URef((int) (uRef.getValue() / powf(2, levelDiff)));
            RRef rrefAtLowerLOD = RRef((int) (rRef.getValue() / powf(2, levelDiff)));
            return new LodTile(LodTile(geocell, lod, urefAtLowerLOD, rrefAtLowerLOD));
        }
    }
    
    std::string LodTile::asString() {
        std::stringstream ss;
        ss << ((getGeocell().getLatitude().isNorth()) ? "N" : "S") << fabs(getGeocell().getLatitude().getValue()) << " ";
        ss << ((getGeocell().getLongitude().isWest()) ? "W" : "E") << fabs(getGeocell().getLongitude().getValue()) << " ";
        ss << "L" << getLevelOfDetail().getValue() << " ";
        ss << "U" << getURef().getValue() << " ";
        ss << "R" << getRRef().getValue();
        return ss.str();
    }
    
    
}
