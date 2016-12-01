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

#ifndef CDB2OSG_PROGRESSIVETILEBUILDER_H
#define CDB2OSG_PROGRESSIVETILEBUILDER_H

#include <CDB2OSG/TileBuilders/LODPolicy.h>
#include <CDB2OSG/TileBuilder.h>
#include <CDB/LodTileQuery.h>
#include "NextTiles.h"

namespace CDB2OSG {
    
    class ProgressiveTileBuilder : public TileBuilder {
        
    public:
        
        void setLodPolicy(LODPolicy *lodPolicy);
        
        void setNextTiles(NextTiles *nextTiles);
        
        void enableElevationSubsampling(bool enable);
        
        virtual osg::Node *build();
        
        virtual void setupMoreDetailedChildForRange(double min, double max, CDB::LodTile::List lodTilesToLoad) = 0;
        
        virtual osg::LOD *getLodNode() = 0;
        
    protected:
        
        osg::ref_ptr<LODPolicy> lodPolicy;
        osg::ref_ptr<NextTiles> nextTiles;
        bool subsamplingEnabled;
        
    };
    
};

#endif
