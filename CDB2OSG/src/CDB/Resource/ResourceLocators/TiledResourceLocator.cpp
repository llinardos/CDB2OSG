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

#include "TiledResourceLocator.h"
#include <CDB/Resource/ResourceLocators/PathSolvers/LatitudePathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/LodPathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/URefPathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/LongitudePathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/LayerPathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/LayerComponentPathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/RRefPathSolver.h>
#include <CDB/Resource/ResourceLocators/PathSolvers/PathSolverUtils.h>

namespace CDB {
    
    TiledResourceLocator::TiledResourceLocator() {
        
    }
    
    std::string TiledResourceLocator::getPath() {
        osg::ref_ptr<CDB::Layer> layer = layerComponent->getLayer();
        std::string fileExtension = layerComponent->getFileExtension();
        Latitude latitude = geocell.getLatitude();
        Longitude longitude = geocell.getLongitude();
        Zone zone = geocell.getZone();
        
        LOD lodLevel = lod;
        
        LatitudePathSolver latitudeNameSolver(geocell.getLatitude());
        LongitudePathSolver longitudeNameSolver(geocell.getLongitude(), zone);
        LayerPathSolver layerNameSolver(layer);
        LayerComponentPathSolver layerComponentNameSolver(layerComponent);
        LodPathSolver lodNameSolver(lodLevel);
        URefPathSolver uRefNameSolver(uref);
        RRefPathSolver rRefNameSolver(rref);
        
#ifdef _WIN32
        std::string directoryTemplate = "\\CDB\\Tiles\\Lat\\Lon\\nnn_DatasetName\\LOD\\UREF\\";
#ifdef _WIN64
        std::string directoryTemplate = "\\CDB\\Tiles\\Lat\\Lon\\nnn_DatasetName\\LOD\\UREF\\";
#endif
#elif __APPLE__
        std::string directoryTemplate = "/CDB/Tiles/Lat/Lon/nnn_DatasetName/LOD/UREF/";
#endif
        
        //		std::string directoryTemplate = "\\CDB\\Tiles\\Lat\\Lon\\nnn_DatasetName\\LOD\\UREF\\";
        PathUtils::replace(directoryTemplate, "Lat", latitudeNameSolver.getFolderNameComponent());
        PathUtils::replace(directoryTemplate, "Lon", longitudeNameSolver.getFolderNameComponent());
        PathUtils::replace(directoryTemplate, "nnn_DatasetName", layerNameSolver.getFolderNameComponent());
        PathUtils::replace(directoryTemplate, "LOD", lodNameSolver.getFolderNameComponent());
        PathUtils::replace(directoryTemplate, "UREF", uRefNameSolver.getFolderNameComponent());
        
        std::string filenameTemplate = "LatLon_Dnnn_Snnn_Tnnn_LOD_Un_Rn";
        PathUtils::replace(filenameTemplate, "Lat", latitudeNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "Lon", longitudeNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "Dnnn", layerNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "Snnn_Tnnn", layerComponentNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "LOD", lodNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "Un", uRefNameSolver.getFileNameComponent());
        PathUtils::replace(filenameTemplate, "Rn", rRefNameSolver.getFileNameComponent());
        
        return directoryTemplate + filenameTemplate + fileExtension;
    }
    
};
