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

#ifndef CDB_DOUBLEVALUE_H
#define CDB_DOUBLEVALUE_H

#include <osg/Referenced>

namespace CDB {
    
    class DoubleValue : public osg::Referenced {
        
    public:
        
        DoubleValue(double value = 0.0);
        
        DoubleValue(int value);
        
        DoubleValue(const DoubleValue &otherValue);
        
        double getValue() const;
        
        DoubleValue &operator=(const DoubleValue &otherLod);
        
        DoubleValue operator+(const DoubleValue &otherValue) const;
        
        DoubleValue operator-(const DoubleValue &otherValue) const;
        
        bool operator==(const DoubleValue &otherValue) const;
        
        bool operator!=(const DoubleValue &otherValue) const;
        
        bool operator<(const DoubleValue &otherValue) const;
        
        bool operator>(const DoubleValue &otherValue) const;
        
        bool operator<=(const DoubleValue &otherValue) const;
        
        bool operator>=(const DoubleValue &otherValue) const;
        
    protected:
        
        double value;
        
    };
    
};

#endif
