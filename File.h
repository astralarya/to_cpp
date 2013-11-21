// File.h
// Mara Kim
// Rokas Lab
// Vanderbilt University
//
// Static functions to manipulate files and directories
// in a POSIX environment

#ifndef FILECOPY_H
#define FILECOPY_H

#include <sys/sendfile.h> // sendfile
#include <fcntl.h> // open
#include <unistd.h> // close
#include <sys/stat.h> // fstat
#include <sys/types.h> // fstat
#include <stdio.h> // remove
#include <errno.h>
#include <string>
#include <sstream>
#include <ios>
#include <cstdlib>

class File {
public:
    static int copy(const char* sourcefile, const char* destfile, int offset = 0);
    static int mkdir(std::string directory);
    static int mkdir(std::string directory, std::string mode);
    static int mkdir(std::string directory, int mode);
    static int chmod(const char* path, int mode);
    static int chmod(const char* path, std::string mode);
};

#endif // FILECOPY_H
