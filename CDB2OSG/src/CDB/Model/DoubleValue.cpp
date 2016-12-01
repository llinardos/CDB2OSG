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

#include "DoubleValue.h"

namespace CDB {
    
    DoubleValue::DoubleValue(double value) : Referenced() {
        DoubleValue::value = value;
    }
    
    DoubleValue::DoubleValue(int value) : Referenced() {
        DoubleValue::value = (double)value;
    }
    
    DoubleValue::DoubleValue(const DoubleValue &otherValue) : value(otherValue.value) {
        
    }
    
    double DoubleValue::getValue() const {
        return value;
    }
    
    DoubleValue &DoubleValue::operator=(const DoubleValue &otherLod) {
        value = otherLod.value;
        return *this;
    }
    
    DoubleValue DoubleValue::operator+(const DoubleValue &otherValue) const {
        return DoubleValue(value + otherValue.value);
    }
    
    DoubleValue DoubleValue::operator-(const DoubleValue &otherValue) const {
        return DoubleValue(value - otherValue.value);
    }
    
    bool DoubleValue::operator==(const DoubleValue &otherValue) const {
        return value == otherValue.value;
    }
    
    bool DoubleValue::operator!=(const DoubleValue &otherValue) const {
        return !((*this) == otherValue);
    }
    
    bool DoubleValue::operator<(const DoubleValue &otherValue) const {
        return value < otherValue.value;
    }
    
    bool DoubleValue::operator>(const DoubleValue &otherValue) const {
        return value > otherValue.value;
    }
    
    bool DoubleValue::operator<=(const DoubleValue &otherValue) const {
        return value <= otherValue.value;
    };
    
    bool DoubleValue::operator>=(const DoubleValue &otherValue) const {
        return value >= otherValue.value;
    };
};
