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

#ifndef CDB_GEOCELL
#define CDB_GEOCELL

#include <osg/ref_ptr>
#include <vector>
#include <osg/Referenced>
#include "Latitude.h"
#include "Longitude.h"
#include "Zone.h"

namespace CDB {
    
    class Geocell : public osg::Referenced {
        
    public:
        
        Geocell(Latitude latitude = Latitude(0), Longitude longitude = Longitude(0));
        
        Geocell(const Geocell &otherGeocell);
        
        Geocell &operator=(const Geocell &otherGeocell);
        
        const Latitude &getLatitude() const;
        
        const Longitude &getLongitude() const;
        
        const Zone &getZone() const;
        
        bool operator==(const Geocell &otherGeocell) const;
        
        bool operator!=(const Geocell &otherGeocell) const;
        
        bool operator<(const Geocell &otherGeocell) const;
        
        bool operator>(const Geocell &otherGeocell) const;
        
        typedef std::vector< osg::ref_ptr<CDB::Geocell> > List;
        
    protected:
        
        Latitude latitude;
        Longitude longitude;
        Zone zone;
        
    };
    
}

#endif
