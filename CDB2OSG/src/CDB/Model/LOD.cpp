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

#include "LOD.h"

namespace CDB {
    
    LOD::LOD(int value) : IntValue(value) {
        
    }
    
    LOD::LOD(const LOD &otherLOD) : IntValue(otherLOD) {
        
    }
    
    bool LOD::valid() const {
        return value >= CDB::Constants::minimumLOD && value <= CDB::Constants::maximumLOD;
    }
    
    unsigned int LOD::getNumberOfDivisions() const {
        return numberOfDivisionsByLodLevel[value];
    }
    
    URef::List LOD::uRefs() const {
        CDB::URef::List uRefs;
        for (unsigned int division = 0; division < this->getNumberOfDivisions(); division++) {
            uRefs.push_back(new CDB::URef(division));
        }
        return uRefs;
    }
    
    RRef::List LOD::rRefs() const {
        CDB::RRef::List rRefs;
        for (unsigned int division = 0; division < this->getNumberOfDivisions(); division++) {
            rRefs.push_back(new CDB::RRef(division));
        }
        return rRefs;
    }
    
    LOD LOD::getMoreDetailedLOD() const {
        return LOD(value + 1);
    }
    
    LOD LOD::getLessDetailedLOD() const {
        return LOD(value - 1);
    }
    
    std::map<int, unsigned int> makeDivisionByLodLevel() {
        std::map<int, unsigned int> divisionByLod;
        CDB::LOD::List allLods = CDB::LOD::all();
        for (unsigned int i = 0; i < allLods.size(); i++) {
            LOD *lod = allLods[i];
            divisionByLod[lod->getValue()] = (unsigned int) powf(2.0, lod->getValue());
        }
        return divisionByLod;
    }
    
    LOD LOD::min() {
        return LOD(Constants::minimumLOD);
    }
    
    LOD LOD::zero() {
        return LOD(0);
    }
    
    LOD LOD::max() {
        return LOD(Constants::maximumLOD);
    }

    LOD::List LOD::all() {
        CDB::LOD::List allLods;
        for (int lodLevel = CDB::Constants::minimumLOD; lodLevel < CDB::Constants::maximumLOD; lodLevel++) {
            allLods.push_back(new CDB::LOD(lodLevel));
        }
        return allLods;
    }
    
    std::map<int, unsigned int> LOD::numberOfDivisionsByLodLevel = makeDivisionByLodLevel();
    
}
