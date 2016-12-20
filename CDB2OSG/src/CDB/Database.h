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

#ifndef CDB_DATABASE
#define CDB_DATABASE

#include <CDB/Model/Model.h>
#include <osg/Referenced>
#include <map>
#include <string>
#include <vector>

namespace CDB {
    
    class Query;
    class Resource;
    
    class Database : public osg::Referenced {
        
    public:
        
        Database(std::string path = "", std::string subsamplingFolderPath = "");
        
        std::string getPath();
        
        std::string getSubsamplingPath();
        
        void enableSubsampling(bool enable);
        
        bool isSubsamplingEnabled();
        
        void addComponentWithName(LayerComponent *component, ComponentName name);
        
        LayerComponent *getComponentWithName(ComponentName name);
        
        virtual Resource* executeQuery(Query *query);
        
    protected:
        
        std::string path;
        std::string subsamplingFolderPath;
        bool subsamplingEnabled;
        
        std::map<ComponentName, osg::ref_ptr<CDB::LayerComponent> > componentsByName;
        
    };
    

    class DatabaseListener {
        
    public:
        
        DatabaseListener() { }
        
        virtual ~DatabaseListener() { }
        
        virtual void databaseWillStartQueryExecution(Database *database, Query *query) = 0;
        
        virtual void databaseDidFinishQueryExecution(Database *database, Query *query) = 0;
        
    };
    


    class MeasureableDatabase : public CDB::Database {
        
    public:
        
        MeasureableDatabase(std::string path = "", std::string subsamplingFolderPath = "");
        
        void addListener(DatabaseListener *listener);
        
        virtual Resource* executeQuery(Query *query);
        
    protected:
        
        std::vector<DatabaseListener *> listeners;
        
    };
    
}

#endif
