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

#include "Layer.h"

namespace CDB {
    
    Layer::Layer(std::string name, unsigned int code) :
        name(name),
        code(code) {
        
    }
    
    Layer::Layer(const Layer &otherDataset) :
        name(otherDataset.name),
        code(otherDataset.code) {
            
    }

    Layer &Layer::operator=(const Layer &ds) {
        name = ds.name;
        code = ds.code;
        return *this;
    }

    const LayerComponent::List &Layer::getComponents() const {
        return components;
    }

    void Layer::addComponent(const osg::ref_ptr<LayerComponent> &component) {
        components.push_back(component);
    }

    const std::string &Layer::getName() const {
        return name;
    }

    unsigned int Layer::getCode() const {
        return code;
    }

    bool Layer::operator==(const Layer &ds) const {
        return code == ds.getCode();
    }

    bool Layer::operator!=(const Layer &ds) const {
        return code != ds.getCode();
    }

    bool Layer::operator<(const Layer &ds) const {
        return code < ds.getCode();
    }

    typedef std::vector<osg::ref_ptr<CDB::Layer> > List;
    
};
