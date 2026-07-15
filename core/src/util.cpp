#include "util.h"

std::string Util::findMediaPath()
{
    LOG("Searching for /media/ folder...");
    std::filesystem::path currentPath = std::filesystem::current_path();
    while (true) {
        std::filesystem::path mediaPath = currentPath / "media";
        if (std::filesystem::exists(mediaPath) && std::filesystem::is_directory(mediaPath)) {
            LOG("/media/ folder found.");
            return mediaPath.generic_string(); 
        }

        if (currentPath == currentPath.parent_path()) {
            break;
        }
        currentPath = currentPath.parent_path();
    }
    LOG("/media/ folder not found. You can introduce it as second argument on .exe. First one is reserved to filter.");
    throw std::runtime_error("Error: /media/ folder not found.");
}

std::string Util::getImageFolder(const std::string& fullPath)
{
    std::filesystem::path path(fullPath);
    return path.parent_path().generic_string();
}