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

#ifndef CDB_MODEL_CONSTANTS
#define CDB_MODEL_CONSTANTS

#include <string>

namespace CDB {
    
    namespace Constants {
        
        static const double dLatCell = 1.0; // defined as the height in degrees of a CDB Geocell
        static const double dLonCellBasic = 1.0; // defined as the width in degrees of a CDB Geocell at the Equator
        static const int minimumLOD = -10;
        static const int maximumLOD = 23;
        
    }
    
    typedef std::string ComponentName;
    const ComponentName PrimaryTerrainElevation = "Primary Terrain Elevation";
    const ComponentName YearlyVSTIRepresentationImagery = "Yearly VSTI Representation";
    
}

#endif
