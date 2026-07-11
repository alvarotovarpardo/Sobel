#pragma once
#include <memory>
#include <opencv2/opencv.hpp>
#include "image.h"

class ImageProcessor{
public:
    static std::unique_ptr<Image> loadImage(const std::string& imagePath);
    static bool saveImage(const std::string& savePath, Image& image);
};