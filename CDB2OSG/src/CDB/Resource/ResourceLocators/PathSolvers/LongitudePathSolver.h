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

#ifndef CDB_LONGITUDEPATHSOLVER_H
#define CDB_LONGITUDEPATHSOLVER_H

#include <CDB/Resource/ResourceLocators/FileNameSolver.h>
#include <CDB/Resource/ResourceLocators/FolderNameSolver.h>
#include <CDB/Model/Zone.h>
#include <CDB/Model/Longitude.h>

namespace CDB {
    
    class LongitudePathSolver : public CDB::FolderNameSolver, public CDB::FileNameSolver {
        
    public:
        
        LongitudePathSolver(const Longitude &longitude, const Zone &zone);
        
        virtual std::string getFolderNameComponent();
        
        virtual std::string getFileNameComponent();
        
    protected:
        
        Longitude longitude;
        Zone zone;
        
        virtual std::string getCommonComponent();
        
    };
    
};


#endif
