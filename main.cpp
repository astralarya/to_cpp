// main.cpp
// A main function that reports help and version info 
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


#include "Initializer.h"
#include "Options.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

int main(int argc, char** argv) {
    // Initialize
    // argcount, argvector, argument usage, description
    Initializer init(argc, argv, "[BOOKMARK...]",
                     "Bookmark file system locations in POSIX-like systems\v"
                     "Only one option allowed at a time");

    // Describe options
    Project::action mode = Project::GO;
    std::vector<std::string> bookmarks;
    std::string path;
    init.option("bookmark", 'b', "PATH", "Create bookmarks to current directory or PATH",
                [&] (char* arg, Initializer::state* state) -> int {
                    if(mode != Project::GO)
                        Initializer::error(state,"Too many modes: '%s'", arg);
                    else
                        mode = Project::CREATE;
                    if(!arg)
                        return 0;
                    if(true) //TODO directory existence check
                        path = arg;
                    else
                        Initializer::error(state,"Not a directory: '%s'", arg);
                    return 0;
                },1);
    init.option("delete", 'd', 0, "Delete bookmarks",
                [&] (char* arg, Initializer::state* state) -> int {
                    if(mode != Project::GO)
                        Initializer::error(state,"Too many modes: '%s'", arg);
                    else
                        mode = Project::DELETE;
                    return 0;
                });
    init.option("print", 'p', 0, "Print bookmarks",
                [&] (char* arg, Initializer::state* state) -> int {
                    if(mode != Project::GO)
                        Initializer::error(state,"Too many modes: '%s'", arg);
                    else
                        mode = Project::PRINT;
                    return 0;
                });
    init.event(Initializer::ARG, // Handle arguments
               [&] (char* arg, Initializer::state* state) -> int {
                   if(strchr(arg,'/'))
                       Initializer::error(state,"Bookmark names may not contain '/': '%s'", arg);
                   else
                       bookmarks.push_back(arg);
                   return 0;
               });
    init.event(Initializer::NO_ARGS, // Check argument count
               [&] (char* arg, Initializer::state* state) -> int {
                   // TODO print bookmarks
                   exit(0);
               });

    // Parse arguments
    init.parse();

    // run program

    return 0;
}
