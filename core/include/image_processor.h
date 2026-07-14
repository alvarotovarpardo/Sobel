#pragma once
#include <memory>
#ifndef __ANDROID__
    #include <opencv2/opencv.hpp>
#endif
#include "image.h"

class ImageProcessor{
public:

#ifndef __ANDROID__
    static std::unique_ptr<Image> loadImage(const std::string& imagePath);
    static bool saveImage(const std::string& savePath, Image& image);
#endif

    
};