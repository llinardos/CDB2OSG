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

#ifndef CDB2OSG_ELEVATIONDATASETSUBSAMPLER_H
#define CDB2OSG_ELEVATIONDATASETSUBSAMPLER_H

#include <CDB/Model/LodTile.h>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <CDB/Database.h>

namespace CDB2OSG {
    
    class ElevationDatasetSubsampler : public osg::Referenced {
        
    public:
        
        CDB::Resource* subsampleLodTileFromLodTileOnDatabase(CDB::LodTile *destinationLodTile,
                                                           CDB::LodTile *sourceLodTile,
                                                           CDB::Database *database);
        
    protected:
        
        CDB::Resource* elevationResourceForLodTile(CDB::LodTile *tile, CDB::Database *db);
        
        CDB::Resource* elevationSubsampledResourceForLodTile(CDB::LodTile *tile, CDB::Database *db);
        
        void coordinates(osg::ref_ptr<osg::HeightField> hf,
                         osg::ref_ptr<CDB::LodTile> sourceLodTile,
                         osg::ref_ptr<CDB::LodTile> destinationLodTile,
                         CDB::Latitude &southLat, CDB::Latitude &northLat, CDB::Longitude &eastLon, CDB::Longitude &westLon);
        
    };
    
}

#endif
