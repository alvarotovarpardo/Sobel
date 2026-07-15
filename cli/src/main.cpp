#include <iostream>
#include <filesystem>
#include "filter_selector.h"
#include "image_processor.h"
#include "util.h"

int main(int argc, char** argv)
{
    std::string filterName = "Sobel";
    std::string imagePath;
    std::string imageFolder;
    if (argc > 1) {
        imagePath = argv[1];
        imageFolder = Util::getImageFolder(imagePath);
        LOG("Using provided path: " + imagePath);
    } else {
        try {
            LOG("No path provided. Searching for media path...");
            imageFolder = Util::findMediaPath();
            imagePath = imageFolder + "/input_sample.jpg";
        } catch (const std::exception& e) {
            LOG("Error finding media path: " + std::string(e.what()));
            return -1;
        }
    }
    std::string outputPath = imagePath + "/output_image.jpg";

    if(argc > 2) {
        filterName = argv[2];
        LOG(filterName + "introduced as input.");
    }

    LOG("Initializing program.");
    try {
        
        std::unique_ptr<Image> pInputImage = ImageProcessor::loadImage(imagePath);
        if(pInputImage == nullptr) return -1;

        std::unique_ptr<FilterBase> pFilter = FilterSelector::createFilter(filterName);
        std::unique_ptr<Image> pOutputImage = nullptr;
        if (pFilter) {
            pOutputImage = std::make_unique<Image>(pFilter->applyFilter(*pInputImage));
        } else {
            std::cerr << "Null filter selected" << std::endl;
        }

        if(!ImageProcessor::saveImage(outputPath, *pOutputImage)) return -1;

    } catch (const std::exception& e) {
        std::cerr << "Execution error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}