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

#ifndef CDB_TILEIDQUERY
#define CDB_TILEIDQUERY

#include <CDB/Query.h>
#include <CDB/Model/LodTile.h>
#include <CDB/Resource/ResourceLocators/TiledResourceLocator.h>
#include <CDB/Model/Model.h>
#include <CDB/ResourceAccessor.h>
#include <CDB/Resource.h>

namespace CDB {
    
    class LodTileQuery : public CDB::Query {
        
    public:
        
        LodTileQuery() { }
        
        CDB::Resource* executeOnDatabase(CDB::Database *database);
        
        void setLodTile(CDB::LodTile *lodTile);
        
        void setComponent(const osg::ref_ptr<CDB::LayerComponent> &component);
        
        const osg::ref_ptr<CDB::LodTile> &getLodTile() const;
        
        const osg::ref_ptr<CDB::LayerComponent> &getComponent() const;
        
    protected:
        
        osg::ref_ptr<CDB::LodTile> lodTile;
        osg::ref_ptr<CDB::LayerComponent> component;
        osg::ref_ptr<CDB::ResourceAccessor> accessor;
        
    };
    
}

#endif
