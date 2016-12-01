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

#include "Resource.h"
#include <fstream>

namespace CDB {
    
    Resource::Resource(Database *database, ResourceLocator *locator) {
        this->database = database;
        this->locator = locator;
    }

    std::string Resource::getPath() {
        return this->database->getPath() + locator->getPath();
    }
    
    bool Resource::exists() {
        std::cout << "EXISTS?: " << this->getPath() << std::endl;
        return std::ifstream(this->getPath().c_str()).good();
    }

};
