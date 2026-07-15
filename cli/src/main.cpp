#include <iostream>
#include <filesystem>
#include "filter_selector.h"
#include "image_processor.h"

int main(int argc, char** argv)
{
    std::string filterName = "sobel";
    if (argc > 1) {
        filterName = argv[1];
    }
    LOG("Initializing program.");
    try {
        
        std::unique_ptr<Image> pImage = ImageProcessor::loadImage("C:/CODE2/Sobel/media/input_sample.jpg");
        if(pImage == nullptr) return -1;

        std::unique_ptr<FilterBase> pFilter = FilterSelector::createFilter(filterName);
        Image outputImage;
        if (pFilter) {
            outputImage = pFilter->applyFilter(*pImage);
        } else {
            std::cerr << "Null filter selected" << std::endl;
        }

        if(!ImageProcessor::saveImage("C:/CODE2/Sobel/media/output_sample.jpg", outputImage)) return -1;

    } catch (const std::exception& e) {
        std::cerr << "Execution error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}