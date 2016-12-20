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

#ifndef CDB_LOD
#define CDB_LOD

#include "Constants.h"
#include "RRef.h"
#include "URef.h"
#include "IntValue.h"
#include <iostream>
#include <map>
#include <math.h>
#include <vector>

namespace CDB {
    
    class LOD : public CDB::IntValue {
        
    public:
        
        typedef std::vector<osg::ref_ptr<CDB::LOD> > List;
        
        LOD(int value = 0);
        
        LOD(const LOD &otherLOD);
        
        bool valid() const;
        
        unsigned int getNumberOfDivisions() const;
        
        URef::List uRefs() const;
        
        RRef::List rRefs() const;
        
        LOD getMoreDetailedLOD() const;
        
        LOD getLessDetailedLOD() const;
        
        static CDB::LOD min();
        
        static CDB::LOD zero();
        
        static CDB::LOD max();
        
        static CDB::LOD::List all();
        
    protected:
        
        static std::map<int, unsigned int> numberOfDivisionsByLodLevel;
        
    };
    
}

#endif
