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

#include "Zone.h"

namespace CDB {
    
    Zone::Zone(int number, Latitude southLimit, Latitude northLimit, double longitudeLatitudeRatio) :
        number(number),
        southLimit(southLimit),
        northLimit(northLimit),
        longitudeLatitudeRatio(longitudeLatitudeRatio) {
            
    }
    
    Zone::Zone(const Zone &otherZone) :
        number(otherZone.number),
        southLimit(otherZone.southLimit),
        northLimit(otherZone.northLimit),
        longitudeLatitudeRatio(otherZone.longitudeLatitudeRatio) {
            
    }
    
    Zone Zone::zoneForLatitude(Latitude latitude) {
        Zone *zoneForLatitude = NULL;
        for (unsigned int zoneIndex = 0; zoneIndex < zones.size(); zoneIndex++) {
            Zone zone = zones[zoneIndex];
            if (zone.includeLatitude(latitude)) {
                zoneForLatitude = &(zone);
                break;
            }
        }
        return (*zoneForLatitude);
    }
    
    Zone &Zone::operator=(const Zone &otherZone) {
        Zone::number = otherZone.number;
        Zone::southLimit = otherZone.southLimit;
        Zone::northLimit = otherZone.northLimit;
        Zone::longitudeLatitudeRatio = otherZone.longitudeLatitudeRatio;
        return *this;
    }
    
    bool Zone::includeLatitude(Latitude latitude) {
        return latitude >= southLimit && latitude < northLimit;
    }
    
    double Zone::latitudeLongitudeRatio() {
        return longitudeLatitudeRatio;
    }
    
    bool Zone::operator==(const Zone &otherZone) const {
        return number == otherZone.number;
    }
    
    bool Zone::operator!=(const Zone &otherZone) const {
        return !((*this) == otherZone);
    }
    
    double Zone::dLonZone() {
        return latitudeLongitudeRatio();
    }
    
    std::vector<Zone> makeZones() {
        std::vector<Zone> zones;
        zones.push_back(Zone(0, Latitude(-90), Latitude(-89), 12));
        zones.push_back(Zone(1, Latitude(-89), Latitude(-80), 6));
        zones.push_back(Zone(2, Latitude(-80), Latitude(-75), 4));
        zones.push_back(Zone(3, Latitude(-75), Latitude(-70), 3));
        zones.push_back(Zone(4, Latitude(-70), Latitude(-50), 2));
        zones.push_back(Zone(5, Latitude(-50), Latitude(50), 1));
        zones.push_back(Zone(6, Latitude(50), Latitude(70), 2));
        zones.push_back(Zone(7, Latitude(70), Latitude(75), 3));
        zones.push_back(Zone(8, Latitude(75), Latitude(80), 4));
        zones.push_back(Zone(0, Latitude(80), Latitude(89), 6));
        zones.push_back(Zone(0, Latitude(89), Latitude(90), 12));
        return zones;
    }
    
    std::vector<Zone> Zone::zones = makeZones();
    
}
