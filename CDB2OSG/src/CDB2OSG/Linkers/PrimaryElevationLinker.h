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

#ifndef CDB2OSG_PRIMARYELEVATIONLINKER_H
#define CDB2OSG_PRIMARYELEVATIONLINKER_H

#include <osg/Referenced>
#include <CDB/Model/LodTile.h>
#include <osg/Shape>
#include <osgTerrain/TerrainTile>

namespace CDB2OSG {
    
    class PrimaryElevationLinker : public osg::Referenced {
        
    public:
        
        PrimaryElevationLinker();
        
        void setHeightFieldFromCDB(osg::HeightField *heightfield);
        
        void setLodTileFromCDB(CDB::LodTile *lodTile);
        
        void setOsgTerrainTile(osgTerrain::TerrainTile *terrainTile);
        
        void setSkirtHeight(float height);
        
        void link();
        
    protected:
        
        osg::ref_ptr<osg::HeightField> heightfield;
        osg::ref_ptr<CDB::LodTile> lodTile;
        osg::ref_ptr<osgTerrain::TerrainTile> terrainTile;
        float skirtHeight;

    };
    
};

#endif
