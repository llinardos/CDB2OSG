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

#include "Latitude.h"

namespace CDB {

    Latitude::Latitude(double value) : DoubleValue(value) {
        
    }

    Latitude::Latitude(int value) : DoubleValue(value) {
        
    }

    Latitude::Latitude(const DoubleValue &otherValue) : DoubleValue(otherValue) {
        
    }

    Latitude Latitude::North(unsigned int value) {
        return Latitude((int) value);
    }

    Latitude Latitude::South(unsigned int value) {
        return Latitude(-(int) value);
    }

    Latitude Latitude::offset(Latitude latitude) const {
        return Latitude(getValue() + latitude.getValue());
    }

    int Latitude::sliceId() const {
        return (int) ((getValue() + 90.0) / CDB::Constants::dLatCell);
    }

    int Latitude::nbSliceID() const {
        return 2 * (int) (90.0 / CDB::Constants::dLatCell);
    }

    bool Latitude::isZero() const {
        return *this == Latitude(0);
    }

    bool Latitude::isNorth() const {
        return *this >= Latitude(0);
    }

    bool Latitude::isSouth() const {
        return *this < Latitude(0);
    }

}
