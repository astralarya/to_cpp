// File.cpp
// Mara Kim

#include "File.h"

int File::chdir(const char* path) {
}

int File::copy(const char* sourcefile, const char* destfile, int offset) {
    int read_fd;
    int write_fd;
    struct stat stat_buf;
    off_t _offset = offset;

     // open input file
    read_fd = open (sourcefile, O_RDONLY);

    // stat the input file
    fstat (read_fd, &stat_buf);

    // delete any existing file
    remove(destfile);

    // open the output file for writing, with the same permissions as source file
    write_fd = open (destfile, O_WRONLY | O_CREAT, stat_buf.st_mode);

    // call the system
    int r = sendfile (write_fd, read_fd, &_offset, stat_buf.st_size);

    // close the files
    close (read_fd);
    close (write_fd);

    if(r == -1)
        return r;
    else
        return 0;
}


int File::mkdir(std::string directory) {
    return mkdir(directory, 0777);
}

int File::mkdir(std::string directory, std::string mode) {
    return mkdir(directory, strtol(mode.c_str(),0,8));
}

int File::mkdir(std::string directory, int mode) {
    struct stat sb;
    const char _delimiter = '/', _escape = '\\';
    int status = 0;
    for(size_t pos = directory.find(_delimiter); pos != std::string::npos; pos = directory.find(_delimiter,pos+1)) {
        if(pos == 0)
            continue;
        else if(pos > 0 && directory[pos-1] == _escape)
            continue;
        else {
            if(stat(directory.substr(0,pos).c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
                continue;
            else {
                if(::mkdir(directory.substr(0,pos).c_str(),mode)) {
                    status = errno;
                    if(status != EEXIST) {
                        std::stringstream ss;
                        ss << std::oct << mode;
                        perror(("File::mkdir(" + directory + ',' + ss.str() + "):").c_str());
                        break;
                    }
                }
            }
        }
    }
    if(!status || status == EEXIST) {
        if(stat(directory.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))
            return 0;
        else {
            if(::mkdir(directory.c_str(),mode)) {
                int status = errno;
                std::stringstream ss;
                ss << std::oct << mode;
                perror(("File::mkdir(" + directory + ',' + ss.str() + "):").c_str());
                return status;
            }
        }
    }
    return status;
}

int File::chmod(const char* path, int mode) {
    if(::chmod(path, mode) == -1) {
        int status = errno;
        std::stringstream ss;
        ss << std::oct << mode;
        perror(("File::chmod(" + std::string(path) + ',' + ss.str() + "):").c_str());
        return status;
    }
    return 0;
}

int File::chmod(const char* path, std::string mode) {
    return chmod(path,strtol(mode.c_str(),0,8));
}
