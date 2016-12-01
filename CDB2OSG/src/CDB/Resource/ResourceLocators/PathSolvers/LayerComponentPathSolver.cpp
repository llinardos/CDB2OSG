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

#include "LayerComponentPathSolver.h"
#include <sstream>
#include <iomanip>

namespace CDB {
    
    LayerComponentPathSolver::LayerComponentPathSolver(const osg::ref_ptr<LayerComponent> &component) : component(component) { }
    
    std::string LayerComponentPathSolver::getFileNameComponent() {
        std::stringstream sstream;
        sstream << "S";
        sstream << std::setw(3) << std::setfill('0') << component->getSelector1().getValue();
        sstream << "_";
        sstream << "T";
        sstream << std::setw(3) << std::setfill('0') << component->getSelector2().getValue();
        return sstream.str();
    }
    
};
