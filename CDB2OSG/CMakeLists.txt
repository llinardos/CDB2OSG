cmake_minimum_required(VERSION 3.3)
project(cdb2osg)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/CDB/Model/LodTile.cpp
        src/CDB/Model/LodTile.h
        src/CDB/Model/Constants.h
        src/CDB/Model/DoubleValue.cpp
        src/CDB/Model/DoubleValue.h
        src/CDB/Model/Geocell.cpp
        src/CDB/Model/Geocell.h
        src/CDB/Model/IntValue.cpp
        src/CDB/Model/IntValue.h
        src/CDB/Model/Latitude.cpp
        src/CDB/Model/Latitude.h
        src/CDB/Model/Layer.cpp
        src/CDB/Model/Layer.h
        src/CDB/Model/LayerComponent.cpp
        src/CDB/Model/LayerComponent.h
        src/CDB/Model/LOD.cpp
        src/CDB/Model/LOD.h
        src/CDB/Model/Longitude.cpp
        src/CDB/Model/Longitude.h
        src/CDB/Model/Model.h
        src/CDB/Model/RRef.cpp
        src/CDB/Model/RRef.h
        src/CDB/Model/Selector.cpp
        src/CDB/Model/Selector.h
        src/CDB/Model/URef.cpp
        src/CDB/Model/URef.h
        src/CDB/Model/Zone.cpp
        src/CDB/Model/Zone.h
        src/CDB/ResourceAccesors/HeightfieldResourceAccesor.cpp
        src/CDB/ResourceAccesors/HeightfieldResourceAccesor.h
        src/CDB/ResourceAccesors/ImageResourceAccesor.cpp
        src/CDB/ResourceAccesors/ImageResourceAccesor.h
        src/CDB/Resource/ResourceLocators/PathSolvers/LatitudePathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/LatitudePathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/LayerComponentPathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/LayerComponentPathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/LayerPathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/LayerPathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/LodPathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/LodPathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/LongitudePathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/LongitudePathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/PathSolverUtils.h
        src/CDB/Resource/ResourceLocators/PathSolvers/RRefPathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/RRefPathSolver.h
        src/CDB/Resource/ResourceLocators/PathSolvers/URefPathSolver.cpp
        src/CDB/Resource/ResourceLocators/PathSolvers/URefPathSolver.h
        src/CDB/Resource/ResourceLocators/FileNameSolver.h
        src/CDB/Resource/ResourceLocators/FolderNameSolver.h
        src/CDB/Resource/ResourceLocators/TiledResourceLocator.cpp
        src/CDB/Resource/ResourceLocators/TiledResourceLocator.h
        src/CDB/ResourceAccessor.cpp
        src/CDB/ResourceAccessor.h
        src/CDB/Resource/ResourceLocator.cpp
        src/CDB/Resource/ResourceLocator.h
        src/CDB/Database.cpp
        src/CDB/Database.h
        src/CDB/Query.cpp
        src/CDB/Query.h
        src/CDB/Resource.cpp
        src/CDB/Resource.h
        src/CDB2OSG/TileBuilders/LODPolicies/CustomLODPolicy.cpp
        src/CDB2OSG/TileBuilders/LODPolicies/CustomLODPolicy.h
        src/CDB2OSG/TileBuilders/LODPolicies/LinearLODPolicy.cpp
        src/CDB2OSG/TileBuilders/LODPolicies/LinearLODPolicy.h
        src/CDB2OSG/TileBuilders/LODPolicies/OnlyLODPolicy.cpp
        src/CDB2OSG/TileBuilders/LODPolicies/OnlyLODPolicy.h
        src/osgOverrides/GeometryTechnique.cpp
        src/osgOverrides/GeometryTechnique.h
        src/osgOverrides/PagedLOD.cpp
        src/osgOverrides/PagedLOD.h
        src/osgOverrides/TerrainTile.h
        src/CDB2OSG/TileBuilders/BasicTileBuilder.cpp
        src/CDB2OSG/TileBuilders/BasicTileBuilder.h
        src/CDB2OSG/Subsampling/ElevationDatasetSubsampler.cpp
        src/CDB2OSG/Subsampling/ElevationDatasetSubsampler.h
        src/CDB2OSG/TileBuilders/NextTiles.cpp
        src/CDB2OSG/TileBuilders/NextTiles.h
        src/CDB2OSG/TileBuilders/PagedLODTileBuilder.cpp
        src/CDB2OSG/TileBuilders/PagedLODTileBuilder.h
        src/CDB2OSG/TileBuilders/LODTileBuilder.cpp
        src/CDB2OSG/TileBuilders/LODTileBuilder.h
        src/CDB2OSG/TileBuilders/ProgressiveTileBuilder.cpp
        src/CDB2OSG/TileBuilders/ProgressiveTileBuilder.h
        src/CDB2OSG/Subsampling/SubsampledResource.cpp
        src/CDB2OSG/Subsampling/SubsampledResource.h
        src/CDB2OSG/Subsampling/SubsampledLodTileQuery.cpp
        src/CDB2OSG/Subsampling/SubsampledLodTileQuery.h
        src/CDB2OSG/TileBuilder.cpp
        src/CDB2OSG/TileBuilder.h
        src/CDB/LodTileQuery.cpp
        src/CDB/LodTileQuery.h
        src/CDB2OSG/Linkers/PrimaryElevationLinker.cpp
        src/CDB2OSG/Linkers/PrimaryElevationLinker.h
        src/CDB2OSG/Linkers/PrimaryImageryLinker.cpp
        src/CDB2OSG/Linkers/PrimaryImageryLinker.h
        src/CDB2OSG/TileBuilders/LODPolicy.h
        src/main.cpp
        src/Utils.h 
	src/CDB2OSG/Functions.cpp 
	src/CDB2OSG/Functions.h
)

FIND_PACKAGE(OpenThreads REQUIRED)
FIND_PACKAGE(OpenSceneGraph REQUIRED osg osgGA osgUtil osgDB osgViewer osgTerrain)

ADD_EXECUTABLE(cdb2osg ${SOURCE_FILES})

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(${OPENSCENEGRAPH_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(cdb2osg ${OPENSCENEGRAPH_LIBRARIES} )
