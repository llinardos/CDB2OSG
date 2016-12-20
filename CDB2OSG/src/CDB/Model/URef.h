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

#ifndef CDB_MODEL_UREF
#define CDB_MODEL_UREF

#include <vector>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include "IntValue.h"

namespace CDB {
    
    class URef : public CDB::IntValue {
        
    public:
        
        URef(int value = 0);
        
        typedef std::vector<osg::ref_ptr<CDB::URef> > List;
        
    };
    
}

#endif
