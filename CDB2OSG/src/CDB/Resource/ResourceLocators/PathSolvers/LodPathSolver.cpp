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

#include "LodPathSolver.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace CDB {
    
    LodPathSolver::LodPathSolver(const LOD &lodLevel) : lodLevel(lodLevel) {
        
    }
    
    std::string LodPathSolver::getFolderNameComponent() {
        std::stringstream sstream;
        
        if (lodLevel.getValue() >= 0) {
            sstream << "L";
            sstream << std::setw(2) << std::setfill('0');
            sstream << lodLevel.getValue();
        } else {
            sstream << "LC";
        }
        
        return sstream.str();
    }
    
    std::string LodPathSolver::getFileNameComponent() {
        std::stringstream sstream;
        
        if (lodLevel.getValue() >= 0) {
            sstream << getFolderNameComponent();
        } else {
            sstream << "LC";
            sstream << std::setw(2) << std::setfill('0');
            sstream << abs(lodLevel.getValue());
        }
        
        return sstream.str();
    }
    
};
