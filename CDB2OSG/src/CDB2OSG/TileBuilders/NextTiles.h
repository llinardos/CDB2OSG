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

#ifndef TILEBUILDERS_NEXTLEVELTILESCONDITION
#define TILEBUILDERS_NEXTLEVELTILESCONDITION

#include <osg/Referenced>
#include <CDB/Model/LodTile.h>
#include <CDB/Model/LayerComponent.h>
#include <CDB/Database.h>

namespace CDB2OSG {
    
    class NextTiles : public osg::Referenced {
        
    public:
        virtual CDB::LodTile::List forLodTile(CDB::LodTile *lodTile) = 0;
        
    };
    
    
    class NextTilesNone : public NextTiles {
        
    public:
        virtual CDB::LodTile::List forLodTile(CDB::LodTile *lodTile);
        
    };
    
    class NextTilesAll : public NextTiles {
        
    public:
        virtual CDB::LodTile::List forLodTile(CDB::LodTile *lodTile);
        
    };
    
    
    class NextTilesExistsComponent : public NextTiles {
        
    public:
        
        NextTilesExistsComponent(CDB::Database *database, std::string componentName);
        
        virtual CDB::LodTile::List forLodTile(CDB::LodTile *lodTile);
        
    protected:
        
        osg::ref_ptr<CDB::Database> database;
        std::string componentName;
        
    };
    
}

#endif
