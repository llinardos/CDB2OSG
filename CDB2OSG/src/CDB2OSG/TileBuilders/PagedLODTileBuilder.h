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

#ifndef CDB2OSG_PAGEDLODTILEBUILDER
#define CDB2OSG_PAGEDLODTILEBUILDER

#include <CDB2OSG/TileBuilders/BasicTileBuilder.h>
#include <CDB/LodTileQuery.h>
#include <CDB2OSG/TileBuilders/ProgressiveTileBuilder.h>
#include <osgOverrides/PagedLOD.h>

namespace CDB2OSG {
    
    class PagedLODTileBuilder : public ProgressiveTileBuilder {
        
    public:
        
        class ReaderCallback;
        
        PagedLODTileBuilder();
        
        virtual void setupMoreDetailedChildForRange(double min, double max, CDB::LodTile::List lodTilesToLoad);
        
        virtual osg::LOD *getLodNode();
        
        virtual ~PagedLODTileBuilder();
        
        class ReaderCallback : public osgDB::ReadFileCallback {
            
        public:
            
            ReaderCallback();
            
            void setTileBuilder(CDB2OSG::TileBuilder *tileBuilder);
            
            virtual ~ReaderCallback();
            
            virtual osgDB::ReaderWriter::ReadResult readNode(const std::string &filename, const osgDB::Options *options);
            
        protected:
            
            osg::ref_ptr<CDB2OSG::TileBuilder> tileBuilder;
            
        };
        
    protected:
        
        osg::ref_ptr<CDB2OSG::PagedLOD> pLod;
        
    };
    
}

#endif
