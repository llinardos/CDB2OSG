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

#include "Longitude.h"

namespace CDB {

    Longitude::Longitude(double value) : DoubleValue(value) {
        
    }

    Longitude::Longitude(int value) : DoubleValue(value) {
        
    }

    Longitude::Longitude(const DoubleValue &otherValue) : DoubleValue(otherValue) {
        
    }

    Longitude Longitude::East(unsigned int value) {
        return Longitude((int) value);
    }

    Longitude Longitude::West(unsigned int value) {
        return Longitude(-(int) value);
    }

    Longitude Longitude::offset(Longitude longitude) const {
        return Longitude(getValue() + longitude.getValue());
    }

    int Longitude::sliceIDIndex(Zone zone) const {
        return (int) ((int) ((getValue() + 180.0) / dLonCell(zone)) * zone.latitudeLongitudeRatio());
    }

    int Longitude::nbSliceIDIndex(Zone zone) const {
        return 2 * (int) (180.0 / dLonCell(zone));
    }

    double Longitude::dLonCell(Zone zone) const {
        return CDB::Constants::dLonCellBasic * zone.dLonZone();
    }

    int Longitude::nbSliceIDIndexEq() const {
        return 2 * (int) (180.0 / CDB::Constants::dLonCellBasic);
    }

    bool Longitude::isZero() const {
        return (*this) == Longitude(0);
    }

    bool Longitude::isEast() const {
        return (*this) >= Longitude(0);
    }

    bool Longitude::isWest() const {
        return (*this) < Longitude(0);
    }
    
};
