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

#include "OnlyLODPolicy.h"

namespace CDB2OSG {

    OnlyLODPolicy::OnlyLODPolicy(CDB::LOD onlyLOD) : LODPolicy(), _onlyLOD(onlyLOD) { }

    void OnlyLODPolicy::rangeLimitsForLOD(CDB::LOD lod, float &min, float &max) {
        if (lod == _onlyLOD) {
            min = 0.0;
            max = FLT_MAX;
        } else {
            min = max = 0.0;
        }
    }

};
