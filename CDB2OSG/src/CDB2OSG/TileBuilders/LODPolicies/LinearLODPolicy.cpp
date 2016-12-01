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

#include "LinearLODPolicy.h"

namespace CDB2OSG {

    LinearLODPolicy::LinearLODPolicy(CDB::LOD baseLOD, double baseMin, double baseMax) : LODPolicy() {
        double rangeMax = FLT_MAX;
        double rangeMin = baseMin;
        double step = fabs((baseMax - baseMin) / (((baseLOD.getValue() + CDB::Constants::maximumLOD) -
                                                   (CDB::Constants::maximumLOD + CDB::Constants::maximumLOD)) + 1));
        for (int lod = baseLOD.getValue(); lod <= CDB::Constants::maximumLOD; lod++) {
            rangeByLod[lod] = osg::Vec2d(rangeMax, rangeMin);
            rangeMax = rangeMin;
            rangeMin -= step;
        }
    }

    void LinearLODPolicy::rangeLimitsForLOD(CDB::LOD lod, float &min, float &max) {
        osg::Vec2d rangeForLOD = rangeByLod[lod.getValue()];
        max = rangeForLOD.x();
        min = rangeForLOD.y();
    }
    
};
