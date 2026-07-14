#pragma once
#include <memory>
#include "image.h"

class ImageProcessor{
public:
    static std::unique_ptr<Image> loadImage(const std::string& imagePath);
    static bool saveImage(const std::string& savePath, Image& image);
};