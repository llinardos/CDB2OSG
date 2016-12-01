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

#include "ElevationDatasetSubsampler.h"
#include <CDB/Resource.h>
#include <CDB/Resource/ResourceLocators/TiledResourceLocator.h>
#include <CDB2OSG/Subsampling/SubsampledResource.h>
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>
#include <osgDB/FileUtils>
#include <osgDB/ReadFile>

namespace CDB2OSG {
    
    CDB::Resource* ElevationDatasetSubsampler::subsampleLodTileFromLodTileOnDatabase(CDB::LodTile *destinationLodTile,
                                                                                   CDB::LodTile *sourceLodTile,
                                                                                   CDB::Database *database) {
        
        osg::ref_ptr<CDB::Resource> sourceResource = this->elevationResourceForLodTile(sourceLodTile, database);
        osg::ref_ptr<osg::HeightField> sourceHF = (new HeightfieldResourceAccesor(sourceResource))->getHeightField();
        
        osg::ref_ptr<CDB::Resource> destinationResource = this->elevationSubsampledResourceForLodTile(destinationLodTile, database);
        
        std::string sourceTilePath = sourceResource->getPath();
        std::string childTilePath = destinationResource->getPath();
        
        CDB::Latitude southa, northa;
        CDB::Longitude westa, easta;
        destinationLodTile->coordinates(southa, northa, easta, westa);
        
        CDB::Latitude south, north;
        CDB::Longitude west, east;
        this->coordinates(sourceHF, sourceLodTile, destinationLodTile, south, north, east, west);
        
        osgDB::makeDirectoryForFile(childTilePath);
        
        std::stringstream gdal_cmd;
#if defined(__APPLE__)
        gdal_cmd << "/usr/local/bin/";
#endif
        gdal_cmd << "gdal_translate -co COMPRESS=lzw -projwin ";
        gdal_cmd << west.getValue() << " ";
        gdal_cmd << north.getValue() << " ";
        gdal_cmd << east.getValue() << " ";
        gdal_cmd << south.getValue() << " ";
        gdal_cmd << "\"" << sourceTilePath << "\"" << " ";
        gdal_cmd << "\"" << childTilePath << "\"";
        
        std::cout << "CMD: " << gdal_cmd.str() << std::endl;
        system(gdal_cmd.str().c_str());
        
        return destinationResource.release();
    }
    
    void ElevationDatasetSubsampler::coordinates(osg::ref_ptr<osg::HeightField> hf,
                                                 osg::ref_ptr<CDB::LodTile> sourceLodTile,
                                                 osg::ref_ptr<CDB::LodTile> destinationLodTile,
                                                 CDB::Latitude &destSouth, CDB::Latitude &destNorth, CDB::Longitude &destEast, CDB::Longitude &destWest) {
        int lodDiff = destinationLodTile->getLevelOfDetail().getValue() - sourceLodTile->getLevelOfDetail().getValue();
        
        CDB::Latitude southLatitude, northLatitude;
        CDB::Longitude westLongitude, eastLongitude;
        
        southLatitude = CDB::Latitude(hf->getOrigin().y());
        westLongitude = CDB::Longitude(hf->getOrigin().x());
        
        northLatitude = CDB::Latitude(hf->getOrigin().y() + hf->getNumColumns() * hf->getXInterval());
        eastLongitude = CDB::Longitude(hf->getOrigin().x() + hf->getNumRows() * hf->getYInterval());
        
        double sourceWidth = fabs(eastLongitude.getValue() - westLongitude.getValue());
        double sourceHeight = fabs(northLatitude.getValue() - southLatitude.getValue());
        
        double destWidth = sourceWidth/powf(2.0, lodDiff);
        double destHeight = sourceHeight/powf(2.0, lodDiff);
        
        int destYOffset = destinationLodTile->getURef().getValue() - (sourceLodTile->getURef().getValue() * powf(2.0, lodDiff));
        int destXOffset = destinationLodTile->getRRef().getValue() - (sourceLodTile->getRRef().getValue() * powf(2.0, lodDiff));
        
        destSouth = southLatitude + (destYOffset * destHeight);
        destNorth = southLatitude + ((destYOffset + 1) * destHeight);
        
        destWest = westLongitude + (destXOffset * destWidth);
        destEast = westLongitude + ((destXOffset + 1) * destWidth);
    }
    
    CDB::Resource* ElevationDatasetSubsampler::elevationResourceForLodTile(CDB::LodTile *tile, CDB::Database *db) {
        osg::ref_ptr<CDB::TiledResourceLocator> tiledLocator = new CDB::TiledResourceLocator();
        
        tiledLocator->layerComponent = db->getComponentWithName(CDB::PrimaryTerrainElevation);
        tiledLocator->geocell = tile->getGeocell();
        tiledLocator->lod = tile->getLevelOfDetail();
        tiledLocator->uref = tile->getURef();
        tiledLocator->rref = tile->getRRef();
        
        return new CDB::Resource(db, tiledLocator);
    }
    
    CDB::Resource* ElevationDatasetSubsampler::elevationSubsampledResourceForLodTile(CDB::LodTile *tile, CDB::Database *db) {
        osg::ref_ptr<CDB::TiledResourceLocator> tiledLocator = new CDB::TiledResourceLocator();
        
        tiledLocator->layerComponent = db->getComponentWithName(CDB::PrimaryTerrainElevation);
        tiledLocator->geocell = tile->getGeocell();
        tiledLocator->lod = tile->getLevelOfDetail();
        tiledLocator->uref = tile->getURef();
        tiledLocator->rref = tile->getRRef();
        
        return new CDB::SubsampledResource(db, tiledLocator);
    }
    
}
