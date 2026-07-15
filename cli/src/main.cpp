#include <iostream>
#include <filesystem>
#include "filter_selector.h"
#include "image_processor.h"

int main(int argc, char** argv)
{
    std::string filterName = "Sobel";
    if (argc > 1) {
        filterName = argv[1];
    }
    LOG("Initializing program.");
    try {
        
        std::unique_ptr<Image> pInputImage = ImageProcessor::loadImage("C:/CODE2/Sobel/media/input_sample.jpg");
        if(pInputImage == nullptr) return -1;

        std::unique_ptr<FilterBase> pFilter = FilterSelector::createFilter(filterName);
        std::unique_ptr<Image> pOutputImage = nullptr;
        if (pFilter) {
            pOutputImage = std::make_unique<Image>(pFilter->applyFilter(*pInputImage));
        } else {
            std::cerr << "Null filter selected" << std::endl;
        }

        if(!ImageProcessor::saveImage("C:/CODE2/Sobel/media/output_sample.jpg", *pOutputImage)) return -1;

    } catch (const std::exception& e) {
        std::cerr << "Execution error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}