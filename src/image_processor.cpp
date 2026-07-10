#include "image_processor.h"

std::unique_ptr<Image> ImageProcessor::loadImage(const std::string& imagePath){
    
    try {
        cv::Mat readMat = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

        if(readMat.empty()){
            throw std::runtime_error("Image could not be loaded.")
        }

        std::unique_ptr<Image> pImage = std::make_unique<Image>();
        pImage->setWidth(readMat.cols);
        pImage->setHeight(readMat.rows);
        pImage->setChannels(readMat.channels());
        
        size_t imageMemSize = readMat.total() * readMat.elemSize();


    } catch(const cv::Exception& error){
        std::cerr << "Load error " << error.what() << "\n";
        return nullptr;
    } catch(const std::bad_alloc& error){
        std::
    }
}