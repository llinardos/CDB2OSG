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

#ifndef CDB2OSG_CUSTOMLODPOLICY_H
#define CDB2OSG_CUSTOMLODPOLICY_H

#include <CDB2OSG/TileBuilders/LODPolicy.h>

namespace CDB2OSG {

class CustomLODPolicy : public LODPolicy {
    
public:
    
    CustomLODPolicy(std::vector<int> limits, int initialLod = -10);

    virtual ~CustomLODPolicy() { }

    virtual void rangeLimitsForLOD(CDB::LOD lod, float &min, float &max);

protected:
    
    typedef std::map<int, osg::Vec2d> RangeByLOD;
    RangeByLOD rangeByLod;
    
};

};

#endif
