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

#include "LayerComponent.h"
#include "Layer.h"

namespace CDB {
    
    LayerComponent::LayerComponent(std::string name,
                   Selector selector1,
                   Selector selector2,
                   std::string fileExtension,
                   CDB::Layer *layer) :
        name(name),
        selector1(selector1),
        selector2(selector2),
        fileExtension(fileExtension),
        layer(layer) {
            
    }
    
    LayerComponent::LayerComponent(const LayerComponent &otherComponent) :
        name(otherComponent.name),
        selector1(otherComponent.selector1),
        selector2(otherComponent.selector2),
        fileExtension(otherComponent.fileExtension),
        layer(otherComponent.layer) {
        
    }
    
    LayerComponent &LayerComponent::operator=(const LayerComponent &c) {
        name = c.name;
        selector1 = c.selector1;
        selector2 = c.selector2;
        fileExtension = c.fileExtension;
        return *this;
    }

    const std::string &LayerComponent::getName() const {
        return name;
    }
    
    const Selector &LayerComponent::getSelector1() const {
        return selector1;
    }
    
    const Selector &LayerComponent::getSelector2() const {
        return selector2;
    }
    
    const std::string &LayerComponent::getFileExtension() const {
        return fileExtension;
    }
    
    Layer *LayerComponent::getLayer() const {
        return layer;
    }
    
    bool LayerComponent::operator==(const LayerComponent &ds) const {
        return selector1 == ds.selector1 && selector2 == ds.selector2;
    }
    
    bool LayerComponent::operator!=(const LayerComponent &ds) const {
        return selector1 != ds.getSelector1() || selector2 != ds.getSelector2();
    }
    
    bool LayerComponent::operator<(const LayerComponent &ds) const {
        return selector1 < ds.getSelector1() && selector2 < ds.getSelector2();
    }
    
}
