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

#ifndef CDB2OSG_TILEBUILDER
#define CDB2OSG_TILEBUILDER

#include <osgTerrain/Terrain>
#include <CDB/Model/LodTile.h>
#include <CDB/Database.h>

namespace CDB2OSG {
    
    class TileBuilder : public osg::Referenced {
        
    public:
        
        TileBuilder();
        
        void setDatabase(CDB::Database *db);
        
        void setTerrain(osgTerrain::Terrain *terrain);
        
        void setLodTile(CDB::LodTile *lodTile);
        
        virtual osg::Node *build() = 0;
        
    protected:
        
        osg::ref_ptr<CDB::Database> database;
        osg::ref_ptr<osgTerrain::Terrain> terrain;
        osg::ref_ptr<CDB::LodTile> lodTile;

    };
    
}

#endif
