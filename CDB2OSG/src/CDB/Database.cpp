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

#include "Database.h"
#include <CDB/Query.h>
#include <CDB/Resource.h>

namespace CDB {
    
    Database::Database(std::string path, std::string subsamplingFolderPath) : path(path), subsamplingFolderPath(subsamplingFolderPath), subsamplingEnabled(false) {
    }
    
    std::string Database::getPath() {
        return path;
    }
    
    std::string Database::getSubsamplingPath() {
        return subsamplingFolderPath;
    }
    
    void Database::enableSubsampling(bool enable) {
        this->subsamplingEnabled = enable;
    }
    
    bool Database::isSubsamplingEnabled() {
        return subsamplingEnabled;
    }
    
    Resource* Database::executeQuery(Query *query) {
        return query->executeOnDatabase(this);
    }
    
    void Database::addComponentWithName(LayerComponent *component, ComponentName name) {
        componentsByName[name] = osg::ref_ptr<LayerComponent>(component);
    }
    
    LayerComponent *Database::getComponentWithName(ComponentName name) {
        return componentsByName[name];
    }
    
    MeasureableDatabase::MeasureableDatabase(std::string path, std::string subsamplingFolderPath) : CDB::Database(path, subsamplingFolderPath) {
        
    }
    
    void MeasureableDatabase::addListener(DatabaseListener *listener) {
        listeners.push_back(listener);
    }
    
    Resource* MeasureableDatabase::executeQuery(Query *query) {
        for (unsigned int i = 0; i < listeners.size(); i++) {
            DatabaseListener *listener = listeners[i];
            listener->databaseWillStartQueryExecution(this, query);
        }
        
        Resource *resource = Database::executeQuery(query);
        
        for (unsigned int i = 0; i < listeners.size(); i++) {
            DatabaseListener *listener = listeners[i];
            listener->databaseDidFinishQueryExecution(this, query);
        }
        
        return resource;
    }
    
}
