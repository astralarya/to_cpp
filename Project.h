// Project.h
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


/** \file Project.h
 *  Globals defining option types
 */

#ifndef PROJECT_H
#define PROJECT_H

#include "Type.h"

/** Project enums */
namespace Project {
    enum string_mode{BOOKMARK_DIR};
    enum action{GO,CREATE,DELETE,PRINT};
}

// Typed modes
template <>
struct Type<Project::string_mode> {
    typedef std::string T;
};

// Overrides
template <>
bool TypeInfo<Project::string_mode>::assign(std::string& var, const std::string& str);

#endif


#ifdef PROJECT_STATICS
/// Static Declarations ///

using namespace Project;

// Mode Signitures
template <>
typename TypeInfo<string_mode>::key_type TypeInfo<string_mode>::keys ({{BOOKMARK_DIR,"BOOKMARK_DIR"}});
template <>
typename TypeInfo<string_mode>::defaults_type TypeInfo<string_mode>::defaults {{BOOKMARK_DIR,{"~/.bookmarks"}}};
template <>
typename TypeInfo<string_mode>::init_type TypeInfo<string_mode>::init {};
template <>
bool TypeInfo<string_mode>::assign(std::string& var, const std::string& str) { var = str; return var==str; }

#endif

