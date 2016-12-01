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

#ifndef CDB_LODTILEID_H
#define CDB_LODTILEID_H

#include <vector>
#include <sstream>
#include <iomanip>
#include <osgTerrain/TerrainTile>
#include <osgTerrain/Locator>
#include <CDB/Model/Model.h>

namespace CDB {

class LodTile : public osg::Referenced {
    
public:
    LodTile(Geocell geocell = Geocell(0, 0),
                   LOD levelOfDetail = LOD(0),
                   URef upIndex = URef(0),
                   RRef rightIndex = RRef(0));
    
    LodTile(Latitude geoCellLatitude,
                   Longitude geoCellLongitude,
                   LOD levelOfDetailValue = LOD(0),
                   URef upIndex = URef(0),
                   RRef rightIndex = RRef(0));

    LodTile(const LodTile &otherLodTile);
    
    LodTile &operator=(const LodTile &otherLodTile);

    bool operator==(const LodTile &otherLodTile) const;

    const Geocell &getGeocell() const;

    const LOD &getLevelOfDetail() const;

    const URef &getURef() const;

    const RRef &getRRef() const;

    typedef std::vector<osg::ref_ptr<CDB::LodTile> > List;
    
    std::string asString();

    virtual ~LodTile() { }

    void coordinates(Latitude &southLat, Latitude &northLat, Longitude &eastLon, Longitude &westLon);

    CDB::LodTile::List getMoreDetailesLodTiles();

    LodTile* getLodTileAtLowerLOD();

protected:
    
    Geocell geocell;
    LOD levelOfDetail;
    URef uRef;
    RRef rRef;

    void addMoreDetailedLodTilesTo(CDB::LodTile::List &lodTilesList, int levelDiff);
    
};

}

#endif
