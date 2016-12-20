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

#ifndef CDB_PATHSOLVERUTILS_H
#define CDB_PATHSOLVERUTILS_H

#include <sstream>

namespace CDB {
    
    class PathUtils {
        
    public:
        
        static void replace(std::string &s, const std::string &search, const std::string &replace) {
            size_t pos = s.find(search, 0);
            if (pos != std::string::npos) {
                s.erase(pos, search.length());
                s.insert(pos, replace);
            }
        }
        
        static inline std::string &rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
            return s;
        }
        
    };
    
};


#endif
