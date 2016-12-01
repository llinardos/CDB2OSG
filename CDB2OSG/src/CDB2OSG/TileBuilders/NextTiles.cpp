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

#include "NextTiles.h"

#include <CDB/LodTileQuery.h>
#include <CDB/ResourceAccesors/ImageResourceAccesor.h>
#include <CDB/ResourceAccesors/HeightfieldResourceAccesor.h>

namespace CDB2OSG {
    
    NextTilesExistsComponent::NextTilesExistsComponent(CDB::Database *database, std::string componentName) {
        this->database = database;
        this->componentName = componentName;
    }
    
    CDB::LodTile::List NextTilesExistsComponent::forLodTile(CDB::LodTile *lodTile) {
        CDB::LodTile::List moreDetailedLodTiles = lodTile->getMoreDetailesLodTiles();
        
        CDB::LodTile::List nextLevelLodTiles;
        for (unsigned int i = 0; i < moreDetailedLodTiles.size(); i++) {
            CDB::LodTile *moreDetailedLodTile = moreDetailedLodTiles[i];
            
            CDB::LodTileQuery *query = new CDB::LodTileQuery();
            query->setComponent(database->getComponentWithName(componentName));
            query->setLodTile(moreDetailedLodTile);
            
            CDB::Resource *resource = query->executeOnDatabase(database);
            
            if (resource->exists()) {
                nextLevelLodTiles.push_back(moreDetailedLodTile);
            }
        }
        return nextLevelLodTiles;
    }
    
    CDB::LodTile::List NextTilesNone::forLodTile(CDB::LodTile *lodTile) {
        CDB::LodTile::List emptyLodTilesList;
        return emptyLodTilesList;
    }
    
    CDB::LodTile::List NextTilesAll::forLodTile(CDB::LodTile *lodTile) {
        return lodTile->getMoreDetailesLodTiles();
    }
    
}
