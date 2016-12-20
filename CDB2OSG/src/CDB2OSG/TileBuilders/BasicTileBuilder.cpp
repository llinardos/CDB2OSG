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

#include "BasicTileBuilder.h"
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>
#include <CDB/ResourceAccesors/ImageResourceAccesor.h>
#include <CDB2OSG/Linkers/PrimaryImageryLinker.h>
#include <CDB2OSG/Linkers/PrimaryElevationLinker.h>
#include <CDB2OSG/Subsampling/SubsampledLodTileQuery.h>

namespace CDB2OSG {
    
    BasicTileBuilder::BasicTileBuilder() {
        shouldQueryForElevation = true;
        shouldQueryForImagery = true;
        shouldSubsampleElevation = false;
    }
    
    
    osg::Node *BasicTileBuilder::build() {
        osg::ref_ptr<CDB::TerrainTile> terrainTile = new CDB::TerrainTile();
        terrainTile->lodTile = lodTile;
        terrainTile->setTerrain(terrain);
        
        if (shouldQueryForElevation) {
            CDB::LodTileQuery *elevationQuery = new CDB::LodTileQuery();
            elevationQuery->setComponent(database->getComponentWithName(CDB::PrimaryTerrainElevation));
            elevationQuery->setLodTile(lodTile);
            
            CDB::Resource *elevationResource = database->executeQuery(elevationQuery);
            
            if (!elevationResource->exists()) {
                if (shouldSubsampleElevation) {
                    osg::ref_ptr<SubsampledLodTileQuery> subsampleQuery = new SubsampledLodTileQuery();
                    subsampleQuery->setLodTile(elevationQuery->getLodTile());
                    subsampleQuery->setComponent(elevationQuery->getComponent());
                    elevationResource = database->executeQuery(subsampleQuery);
                }
            }
            
            if (elevationResource->exists()) {
                osg::HeightField *heightfield = (new HeightfieldResourceAccesor(elevationResource))->getHeightField();
                
                PrimaryElevationLinker *elevationLinker = new PrimaryElevationLinker();
                elevationLinker->setHeightFieldFromCDB(heightfield);
                elevationLinker->setLodTileFromCDB(lodTile);
                elevationLinker->setOsgTerrainTile(terrainTile);
                elevationLinker->setSkirtHeight(50.0);
                elevationLinker->link();
            }
        }
        
        if (shouldQueryForImagery) {
            CDB::LodTileQuery *imageryQuery = new CDB::LodTileQuery();
            imageryQuery->setComponent(database->getComponentWithName(CDB::YearlyVSTIRepresentationImagery));
            imageryQuery->setLodTile(lodTile);
            
            CDB::Resource *imageryResource = database->executeQuery(imageryQuery);
            
            if (imageryResource->exists()) {
                osg::Image *image = (new ImageResourceAccesor(imageryResource))->getImage();
                
                PrimaryImageryLinker *imageryLinker = new PrimaryImageryLinker(0);
                imageryLinker->setImageFromCDB(image);
                imageryLinker->setLodTileFromCDB(lodTile);
                imageryLinker->setOsgTerrainTile(terrainTile);
                imageryLinker->link();
            }
        }
        
        return terrainTile;
    }
    
    void BasicTileBuilder::enableElevationSubsampling(bool enable) {
        shouldSubsampleElevation = enable;
    }
    
    void BasicTileBuilder::enableImageryQuerying(bool enable) {
        shouldQueryForImagery = enable;
    }
    
    void BasicTileBuilder::enableElevationQuerying(bool enable) {
        shouldQueryForElevation = enable;
    }
    
    
}
