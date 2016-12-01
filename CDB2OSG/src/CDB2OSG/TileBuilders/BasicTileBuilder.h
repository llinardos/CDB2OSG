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

#ifndef CDB2OSG_BASICTILEBUILDER
#define CDB2OSG_BASICTILEBUILDER


#include <CDB/Model/LodTile.h>
#include <CDB/Database.h>
#include <CDB2OSG/TileBuilder.h>

#include <osgTerrain/Terrain>
//#include <osgTerrain/TerrainTile>
#include "osgOverrides/TerrainTile.h"

namespace CDB2OSG {
    
    class BasicTileBuilder : public TileBuilder {
        
    public:
        
        BasicTileBuilder();
        
        void enableElevationSubsampling(bool enable);
        
        void enableImageryQuerying(bool enable);
        
        void enableElevationQuerying(bool enable);
        
        osg::Node *build();
        
    protected:
        
        bool shouldSubsampleElevation;
        bool shouldQueryForImagery;
        bool shouldQueryForElevation;
        
    };
    
}

#endif
