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

#include "LatitudePathSolver.h"
#include <sstream>
#include <iomanip>

namespace CDB {
    
    LatitudePathSolver::LatitudePathSolver(const Latitude &latitude) : latitude(latitude) {
        
    }
    
    std::string LatitudePathSolver::getFolderNameComponent() {
        return getCommonComponent();
    }
    
    std::string LatitudePathSolver::getFileNameComponent() {
        return getCommonComponent();
    }
    
    std::string LatitudePathSolver::getCommonComponent() {
        std::stringstream sstream;
        
        int sliceID = latitude.sliceId();
        int nbSliceID = latitude.nbSliceID();
        
        if (latitude.isNorth()) {
            sstream << "N";
            sstream << std::setw(2) << std::setfill('0');
            sstream << sliceID - (nbSliceID / 2);
        } else {
            sstream << "S";
            sstream << std::setw(2) << std::setfill('0');
            sstream << (nbSliceID / 2) - sliceID;
        }
        
        return sstream.str();
    }
    
};
