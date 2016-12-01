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

#include "Geocell.h"

namespace CDB {

    Geocell::Geocell(Latitude latitude, Longitude longitude) :
        latitude(latitude),
        longitude(longitude),
        zone(Zone::zoneForLatitude(latitude)) {
            
    }
    
    Geocell::Geocell(const Geocell &otherGeocell) :
        latitude(otherGeocell.latitude),
        longitude(otherGeocell.longitude),
        zone(Zone::zoneForLatitude(otherGeocell.latitude)) {
            
    }

    Geocell &Geocell::operator=(const Geocell &otherGeocell) {
        latitude = otherGeocell.latitude;
        longitude = otherGeocell.longitude;
        zone = otherGeocell.zone;
        return *this;
    }

    const Latitude &Geocell::getLatitude() const {
        return latitude;
    }

    const Longitude &Geocell::getLongitude() const {
        return longitude;
    }

    const Zone &Geocell::getZone() const {
        return zone;
    }

    bool Geocell::operator==(const Geocell &otherGeocell) const {
        return getLatitude() == otherGeocell.getLatitude() && getLongitude() == otherGeocell.getLongitude();
    }

    bool Geocell::operator!=(const Geocell &otherGeocell) const {
        return !((*this) == otherGeocell);
    }

    bool Geocell::operator<(const Geocell &otherGeocell) const {
        return (getLatitude() < otherGeocell.getLatitude()) && (getLongitude() < otherGeocell.getLongitude());
    }

    bool Geocell::operator>(const Geocell &otherGeocell) const {
        return (getLatitude() > otherGeocell.getLatitude()) && (getLongitude() > otherGeocell.getLongitude());
    }

};
