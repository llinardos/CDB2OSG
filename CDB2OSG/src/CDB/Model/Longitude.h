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

#ifndef CDB_MODEL_LONGITUDE
#define CDB_MODEL_LONGITUDE

#include "DoubleValue.h"
#include "Constants.h"
#include "Zone.h"

namespace CDB {
    
    class Longitude : public DoubleValue {
        
    public:
        
        Longitude(double value = 0.0);
        
        Longitude(int value);
        
        Longitude(const DoubleValue &otherValue);
        
        static Longitude East(unsigned int value);
        
        static Longitude West(unsigned int value);
        
        Longitude offset(Longitude longitude) const;
        
        int sliceIDIndex(Zone zone) const;
        
        int nbSliceIDIndex(Zone zone) const;
        
        double dLonCell(Zone zone) const;
        
        int nbSliceIDIndexEq() const;
        
        bool isZero() const;
        
        bool isEast() const;
        
        bool isWest() const;
        
    };
    
}

#endif
