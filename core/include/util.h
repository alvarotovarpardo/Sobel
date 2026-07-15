#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <filesystem>
#include <stdexcept>
#include "logger.h"

class Util {
public:
    Util() = delete;

    static std::string findMediaPath();
    static std::string getImageFolder(const std::string& fullPath);
    static std::string getImageFormat(const std::string& path);
};

#endif // UTIL_H