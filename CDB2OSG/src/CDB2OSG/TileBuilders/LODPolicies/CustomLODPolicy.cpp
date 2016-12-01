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

#include "CustomLODPolicy.h"

namespace CDB2OSG {

    CustomLODPolicy::CustomLODPolicy(std::vector<int> limits, int initialLod) : LODPolicy() {
        float previousLimit = FLT_MAX;
        int currentLod = initialLod;
        for (unsigned int i = 0; i < limits.size(); i++) {
            int limit = limits[i];

            rangeByLod[currentLod] = osg::Vec2d((double) previousLimit, (double) limit);

            previousLimit = limit;
            currentLod++;
        }
        rangeByLod[currentLod] = osg::Vec2d((double) previousLimit, (double) 0);
    }

    void CustomLODPolicy::rangeLimitsForLOD(CDB::LOD lod, float &min, float &max) {
        osg::Vec2d rangeForLOD = rangeByLod[lod.getValue()];
        max = rangeForLOD.x();
        min = rangeForLOD.y();
    }

};
