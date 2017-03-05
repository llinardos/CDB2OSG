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

#include <CDB/Database.h>

#if defined(__APPLE__)

#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <CDB2OSG/TileBuilders/LODPolicy.h>
#include <CDB2OSG/TileBuilders/PagedLODTileBuilder.h>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgViewer/CompositeViewer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <CDB2OSG/TileBuilders/LODPolicies/CustomLODPolicy.h>

#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>
#include <osgDB/FileUtils>
#include <osgText/Text>
#include <CDB/Model/Model.h>

#include <osgOverrides/GeometryTechnique.h>

struct SampleDatabase {
    std::string name;
    CDB::LodTile::List tiles;
    bool subsampling;
};

class Main : public osg::Referenced {
    
public:
    int width = 1680;
    int height = 1050;
    
    SampleDatabase database;
    
    osgViewer::View *makeView(osg::Node *scene,
                              int originX, int originY, int width, int height,
                              osg::Vec4d clearColor) {
        osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
        traits->x = originX;
        traits->y = originY;
        traits->width = width;
        traits->height = height;
        traits->windowDecoration = true;
        traits->doubleBuffer = true;
        traits->sharedContext = 0;
        
        osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
        if (gc.valid()) {
            osg::notify(osg::INFO) << "  GraphicsWindow has been created successfully." << std::endl;
            
            // need to ensure that the window is cleared make sure that the complete window is set the correct colour
            // rather than just the parts of the window that are under the camera's viewports
            gc->setClearColor(osg::Vec4f(0.2f, 0.2f, 0.6f, 1.0f));
            gc->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        } else {
            osg::notify(osg::NOTICE) << "  GraphicsWindow has not been created successfully." << std::endl;
        }
        
        osg::ref_ptr<osgViewer::View> view = new osgViewer::View;
        
        view->setSceneData(scene);
        view->getCamera()->setViewport(new osg::Viewport(0, 0, width, height));
        view->getCamera()->setGraphicsContext(gc.get());
        
        view->addEventHandler(new osgGA::StateSetManipulator(view->getCamera()->getOrCreateStateSet()));
        view->addEventHandler(new osgViewer::ThreadingHandler);
        view->addEventHandler(new osgViewer::WindowSizeHandler);
        view->addEventHandler(new osgViewer::StatsHandler);
        
        view->getCamera()->setClearColor(clearColor);
        
        return view.release();
    }
    
    CDB::Database *getDatabase(SampleDatabase database, std::string rootPath) {
        std::string selectedDBName = database.name;
        
        std::string subsampledPath = rootPath + "/Subsampled/" + selectedDBName;
        
        osg::ref_ptr<CDB::Database> cdbDatabase = new CDB::Database(rootPath + selectedDBName, subsampledPath);
        cdbDatabase->enableSubsampling(database.subsampling);
        
        osg::ref_ptr<CDB::Layer> elevationLayer = new CDB::Layer("Elevation", 1);
        osg::ref_ptr<CDB::LayerComponent> primaryElevationComponent = new CDB::LayerComponent("Primary Terrain Elevation",
                                                                                              CDB::Selector(1), CDB::Selector(1),
                                                                                              ".tif",
                                                                                              elevationLayer);
        
        elevationLayer->addComponent(primaryElevationComponent);
        cdbDatabase->addComponentWithName(primaryElevationComponent, CDB::PrimaryTerrainElevation);
        
        osg::ref_ptr<CDB::Layer> imageryLayer = new CDB::Layer("Imagery", 4);
        osg::ref_ptr<CDB::LayerComponent> yearlyVSTIRepresentationComponent = new CDB::LayerComponent("Yearly VSTI Representation",
                                                                                                      CDB::Selector(1), CDB::Selector(1),
                                                                                                      ".jp2",
                                                                                                      imageryLayer);
        imageryLayer->addComponent(yearlyVSTIRepresentationComponent);
        cdbDatabase->addComponentWithName(yearlyVSTIRepresentationComponent, CDB::YearlyVSTIRepresentationImagery);
        
        return cdbDatabase.release();
    }
    
    virtual int execute(int argc, char **argv, std::string rootPath) = 0;
};


class SimpleMain : public Main {
public:
    
    int execute(int argc, char **argv, std::string rootPath) {
        double sampleRatio = 1;
        
        osg::ref_ptr<osgViewer::CompositeViewer> viewer = new osgViewer::CompositeViewer();
        
        osg::ref_ptr<CDB::Database> cdbDatabase = getDatabase(database, rootPath);
        
        osg::ref_ptr<osg::Group> terrainScene = new osg::Group();
        
        osg::ref_ptr<osgTerrain::Terrain> terrain = new osgTerrain::Terrain();
        terrain->setEllipsoidModel(new osg::EllipsoidModel());
        terrain->setTerrainTechniquePrototype(new CDB::GeometryTechnique());
        terrain->setSampleRatio(1 / powf(2.0, 2.0f * sampleRatio));
        
        std::vector<int> limits;
        limits.push_back(80000); // L0 -> L1
        limits.push_back(60000); // L1 -> L2
        limits.push_back(30000); // L2 -> L3
        limits.push_back(10000); // L3 -> L4
        limits.push_back(9000);  // L4 -> L5
        limits.push_back(8000);  // L5 -> L6
        limits.push_back(7000);  // L6 -> L7
        limits.push_back(6000);  // L7 -> L8
        osg::ref_ptr<CDB2OSG::CustomLODPolicy> lodPolicy = new CDB2OSG::CustomLODPolicy(limits, 0);
        
        osg::ref_ptr<CDB2OSG::PagedLODTileBuilder> tileBuilder = new CDB2OSG::PagedLODTileBuilder();
        tileBuilder->setLodPolicy(lodPolicy);
        tileBuilder->enableElevationSubsampling(cdbDatabase->isSubsamplingEnabled());
        if (cdbDatabase->isSubsamplingEnabled()) {
            osg::ref_ptr<CDB2OSG::NextTilesExistsComponent> nextTiles = new CDB2OSG::NextTilesExistsComponent(cdbDatabase, CDB::YearlyVSTIRepresentationImagery);
            tileBuilder->setNextTiles(nextTiles);
        } else {
            osg::ref_ptr<CDB2OSG::NextTilesExistsComponent> nextTiles = new CDB2OSG::NextTilesExistsComponent(cdbDatabase, CDB::PrimaryTerrainElevation);
            tileBuilder->setNextTiles(nextTiles);
        }
        
        for (unsigned int i = 0; i < database.tiles.size(); i++) {
            CDB::LodTile *lodTile= database.tiles[i];
            
            osg::ref_ptr<CDB::LodTileQuery> elevationQuery = new CDB::LodTileQuery();
            elevationQuery->setComponent(cdbDatabase->getComponentWithName(CDB::PrimaryTerrainElevation));
            elevationQuery->setLodTile(lodTile);
            osg::ref_ptr<CDB::Resource> resource = elevationQuery->executeOnDatabase(cdbDatabase);
            if (!resource->exists()) {
                std::cerr << "The elevation resource for LOD-tile <" <<  lodTile->asString() << "> for the dabatabase <" << cdbDatabase->getPath() << "> NOT exists. The resource should exists for " << std::endl;
                return false;
            }

            
            tileBuilder->setDatabase(cdbDatabase);
            tileBuilder->setTerrain(terrain);
            tileBuilder->setLodTile(lodTile);
            osg::ref_ptr<osg::Node> tile = tileBuilder->build();
            
            terrainScene->addChild(tile);
        }
        
        osg::ref_ptr<osgViewer::View> view = makeView(terrainScene, 10, 50, width, height, osg::Vec4d(135.0/255.0, 206.0/255.0, 235.0/255.0, 1.0));
        viewer->addView(view);
        
        viewer->run();
        
        return true;
    }
    
    virtual ~SimpleMain() { }
    
};


void split(const std::string &s, char delim, std::vector<std::string> &elems, bool removeDelimeter = true) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (removeDelimeter) {
            elems.push_back(item);
        } else {
            if (elems.size() > 0) {
                std::string itemWithDelimeter = std::string(1, delim) + item;
                elems.push_back(itemWithDelimeter);
            } else {
                elems.push_back(item);
            }
        }
    }
}


std::vector<std::string> split(const std::string &s, char delim, bool removeDelimeter = true) {
    std::vector<std::string> elems;
    split(s, delim, elems, removeDelimeter);
    return elems;
}

CDB::LodTile::List tilesFromString(std::string tilesAsString) {
    std::vector<std::string> tilesStrings = split(tilesAsString, ':');
    
    CDB::LodTile::List lodTiles = CDB::LodTile::List();
    for (int i = 0; i < tilesStrings.size(); i++) {
        std::string tileString = tilesStrings[i];
        std::vector<std::string> latAndLong = split(tileString, 'W', false);
        if (latAndLong.size() == 1) {
            latAndLong = split(tileString, 'E');
        }
        std::string latString = latAndLong[0];
        std::string lonString = latAndLong[1];
        
        CDB::Latitude lat;
        CDB::Longitude lon;
        
        if (latString.size() == 0 || lonString.size() == 0) {
            std::cerr << "Can't parse tile " << tileString << std::endl;
            return CDB::LodTile::List();
        }
        
        
        if (latString[0] == 'N') {
            latString.erase(0, 1);
            int latInt = std::stoi(latString);
            lat = CDB::Latitude::North(latInt);
        }
        if (latString[0] == 'S') {
            latString.erase(0, 1);
            int latInt = std::stoi(latString);
            lat = CDB::Latitude::South(latInt);
        }
        
        if (lonString[0] == 'W') {
            lonString.erase(0, 1);
            int lonInt = std::stoi(lonString);
            lon = CDB::Longitude::West(lonInt);
        }
        if (lonString[0] == 'E') {
            lonString.erase(0, 1);
            int lonInt = std::stoi(lonString);
            lon = CDB::Longitude::East(lonInt);
        }
        
        CDB::LodTile *lodTile = new CDB::LodTile(lat, lon);
        lodTiles.push_back(lodTile);
        
        std::cout << lodTile->asString() << std::endl;
    }
    
    return lodTiles;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "use: CDB2OSG [path] [databaseName] [tiles]" << std::endl;
        return 0;
    }
    
    std::string sampleDbName = argv[2];
    std::string rootPath = argv[1];
    std::string tilesFromCommandLine = argv[3];
    
    if (rootPath.size() == 0) {
        std::cerr << "You need to define a rootPath." << std::endl;
        return 0;
    }
    
    CDB::LodTile::List sampleTiles = tilesFromString(tilesFromCommandLine);
    
    SampleDatabase sampleDB = SampleDatabase();
    sampleDB.name = sampleDbName;
    sampleDB.tiles = sampleTiles;
    sampleDB.subsampling = true;
    
    Main *main = new SimpleMain();
    main->database = sampleDB;
    main->execute(argc, argv, rootPath);
    main = NULL;
}
