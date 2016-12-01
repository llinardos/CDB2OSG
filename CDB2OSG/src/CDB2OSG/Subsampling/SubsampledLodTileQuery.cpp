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

#import "SubsampledLodTileQuery.h"
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>
#include <CDB2OSG/Subsampling/ElevationDatasetSubsampler.h>

namespace CDB2OSG {
    
    SubsampledLodTileQuery::SubsampledLodTileQuery() {
        
    }
    
    CDB::Resource* SubsampledLodTileQuery::executeOnDatabase(CDB::Database *database) {
        osg::ref_ptr<ElevationDatasetSubsampler> subsampler = new ElevationDatasetSubsampler();
        
        osg::ref_ptr<CDB::LodTile> lowerLevelLodTile = lodTile;
        osg::ref_ptr<CDB::Resource> resource;
        do {
            lowerLevelLodTile = lowerLevelLodTile->getLodTileAtLowerLOD();
            
            LodTileQuery *elevationQuery = new LodTileQuery();
            elevationQuery->setComponent(database->getComponentWithName(CDB::PrimaryTerrainElevation));
            elevationQuery->setLodTile(lowerLevelLodTile);
            
            resource = elevationQuery->executeOnDatabase(database);
        } while (!resource->exists());

        CDB::Resource *subsampledResource = subsampler->subsampleLodTileFromLodTileOnDatabase(lodTile, lowerLevelLodTile, database);
        return subsampledResource;
    }
    
    CDB::Resource* SubsampledLodTileQuery::elevationResourceForLodTile(CDB::LodTile *tile, CDB::Database *db) {
        osg::ref_ptr<CDB::TiledResourceLocator> tiledLocator = new CDB::TiledResourceLocator();
        
        tiledLocator->layerComponent = db->getComponentWithName(CDB::PrimaryTerrainElevation);
        tiledLocator->geocell = tile->getGeocell();
        tiledLocator->lod = tile->getLevelOfDetail();
        tiledLocator->uref = tile->getURef();
        tiledLocator->rref = tile->getRRef();
        
        return new CDB::Resource(db, tiledLocator);
    }
    
}
