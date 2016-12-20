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

#import "LodTileQuery.h"
#include <CDB2OSG/Subsampling/SubsampledLodTileQuery.h>

namespace CDB {
    
    CDB::Resource* LodTileQuery::executeOnDatabase(CDB::Database *database) {
        osg::ref_ptr<CDB::TiledResourceLocator> tiledLocator = new CDB::TiledResourceLocator();
        tiledLocator->layerComponent = component;
        tiledLocator->geocell = lodTile->getGeocell();
        tiledLocator->lod = lodTile->getLevelOfDetail();
        tiledLocator->uref = lodTile->getURef();
        tiledLocator->rref = lodTile->getRRef();
        
        return new CDB::Resource(database, tiledLocator);
    }
    
    void LodTileQuery::setLodTile(CDB::LodTile *lodTile) {
        this->lodTile = lodTile;
    }
    
    void LodTileQuery::setComponent(const osg::ref_ptr<CDB::LayerComponent> &component) {
        this->component = component;
    }
    
    const osg::ref_ptr<CDB::LodTile> &LodTileQuery::getLodTile() const {
        return lodTile;
    }
    
    const osg::ref_ptr<CDB::LayerComponent> &LodTileQuery::getComponent() const {
        return component;
    }
        
}
