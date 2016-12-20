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

#ifndef CDB_PagedLOD
#define CDB_PagedLOD

#include <osg/PagedLOD>
#include <osgTerrain/Terrain>
#include <osgDB/Options>
#include <CDB/Model/LodTile.h>

namespace CDB2OSG {
    
    class PagedLOD : public osg::PagedLOD {
        public :
        
        static const std::string LodTilesToLoadKeyOnOptionsPluginData;
        
        PagedLOD();
        
        CDB::LodTile::List getLodTilesToLoad();
        
        PagedLOD(const PagedLOD &plod, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY);
        PagedLOD(PagedLOD &plod, const osg::CopyOp &copyop = osg::CopyOp::SHALLOW_COPY);
        
        META_Node(CDB, PagedLOD);
        
        class DatabaseRequest : public osg::Referenced {
        public:
            bool valid() {
                return true;
            }
        };
        
        
        virtual void addLodTilesToLoadForRange(CDB::LodTile::List lodTiles, float min, float max);
        
        virtual unsigned int getNumTiles() const;
        
        void traverse(osg::NodeVisitor &nv);
        
        protected :
        
        CDB::LodTile::List lodTilesToLoad;
        
        virtual ~PagedLOD();
        
    };
    
}

#endif
