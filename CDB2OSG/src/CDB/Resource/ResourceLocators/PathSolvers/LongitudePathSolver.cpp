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

#include "LongitudePathSolver.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace CDB {
    
    LongitudePathSolver::LongitudePathSolver(const Longitude &longitude, const Zone &zone) :
        longitude(longitude),
        zone(zone) {
        
    }
    
    std::string LongitudePathSolver::getFolderNameComponent() {
        return getCommonComponent();
    }
    
    std::string LongitudePathSolver::getFileNameComponent() {
        return getCommonComponent();
    }
    
    std::string LongitudePathSolver::getCommonComponent() {
        std::stringstream sstream;
        
        int sliceIDIndex = longitude.sliceIDIndex(zone);
        int nbSliceIDIndexEq = longitude.nbSliceIDIndexEq();
        
        if (longitude.isEast()) {
            sstream << "E";
            sstream << std::setw(3) << std::setfill('0');
            sstream << sliceIDIndex - (nbSliceIDIndexEq / 2);
        } else {
            sstream << "W";
            sstream << std::setw(3) << std::setfill('0');
            sstream << (nbSliceIDIndexEq / 2) - sliceIDIndex;
        }
        
        return sstream.str();
    }
    
};
