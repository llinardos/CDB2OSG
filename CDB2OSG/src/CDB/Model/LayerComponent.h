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

#ifndef CDB_LAYER_COMPONENT
#define CDB_LAYER_COMPONENT

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <CDB/Model/Selector.h>
#include <iomanip>
#include <string.h>
#include <sstream>
#include <vector>

namespace CDB {
    
    class Layer;
    
    class LayerComponent : public osg::Referenced {
        
    public:
        
        LayerComponent(std::string name = "",
                       Selector selector1 = Selector(0),
                       Selector selector2 = Selector(0),
                       std::string fileExtension = "",
                       CDB::Layer *layer = NULL);
        
        LayerComponent(const LayerComponent &otherComponent);
        
        LayerComponent &operator=(const LayerComponent &c);
        
        const std::string &getName() const;
        
        const Selector &getSelector1() const;
        
        const Selector &getSelector2() const;
        
        const std::string &getFileExtension() const;
        
        Layer *getLayer() const;
        
        bool operator==(const LayerComponent &ds) const;
        
        bool operator!=(const LayerComponent &ds) const;
        
        bool operator<(const LayerComponent &ds) const;
        
        typedef std::vector< osg::ref_ptr<LayerComponent> > List;
        
    protected:
        
        std::string name;
        Selector selector1;
        Selector selector2;
        std::string fileExtension;
        osg::ref_ptr<Layer> layer;
        
    };
    
}

#endif
