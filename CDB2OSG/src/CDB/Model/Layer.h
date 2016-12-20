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

#ifndef CDB_LAYER
#define CDB_LAYER

#include <osg/Referenced>
#include <iomanip>
#include <map>
#include <sstream>
#include <vector>
#include "LayerComponent.h"

namespace CDB {
    
    class Layer : public osg::Referenced {
        
    public:
        
        Layer(std::string name = "", unsigned int code = 0);
        
        Layer(const Layer &otherDataset);
        
        Layer &operator=(const Layer &ds);
        
        const LayerComponent::List &getComponents() const;
        
        void addComponent(const osg::ref_ptr<LayerComponent> &component);
        
        const std::string &getName() const;
        
        unsigned int getCode() const;
        
        bool operator==(const Layer &ds) const;
        
        bool operator!=(const Layer &ds) const;
        
        bool operator<(const Layer &ds) const;
        
        typedef std::vector< osg::ref_ptr<CDB::Layer> > List;
        
    protected:
        
        std::string name;
        unsigned int code;
        LayerComponent::List components;
        
    };
    
}

#endif
