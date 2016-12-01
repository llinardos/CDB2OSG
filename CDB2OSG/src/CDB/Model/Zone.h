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

#ifndef CDB_ZONE
#define CDB_ZONE

#include <iostream>
#include <vector>
#include <map>
#include "Latitude.h"

namespace CDB {
    
    class Zone {
        
    public:
        
        static Zone zoneForLatitude(Latitude latitude);
        
        Zone(int number, Latitude southLimit, Latitude northLimit, double longitudeLatitudeRatio);
        
        Zone(const Zone &otherZone);
        
        Zone &operator=(const Zone &otherZone);
        
        bool includeLatitude(Latitude latitude);
        
        double latitudeLongitudeRatio();
        
        bool operator==(const Zone &otherZone) const;
        
        bool operator!=(const Zone &otherZone) const;
        
        double dLonZone();

        
    protected:
        
        static std::vector<Zone> zones;
        
        unsigned int number;
        Latitude southLimit;
        Latitude northLimit;
        double longitudeLatitudeRatio;
        
    };
    
}

#endif
