#include "image_processor.h"

std::unique_ptr<Image> ImageProcessor::loadImage(const std::string& imagePath){
    
    try {
        cv::Mat readMat = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

        if(readMat.empty()){
            throw std::runtime_error("Image could not be loaded.");
        }

        std::unique_ptr<Image> pImage = std::make_unique<Image>();
        pImage->setWidth(readMat.cols);
        pImage->setHeight(readMat.rows);
        pImage->setChannels(readMat.channels());
        
        size_t imageMemSize = readMat.total() * readMat.elemSize();
        pImage->resize(imageMemSize);
        std::memcpy(pImage->matData.data(), readMat.ptr(), imageMemSize);
        return pImage;
    } catch(const cv::Exception& error){
        std::cerr << "LoadImage - Load error " << error.what() << "\n";
        return nullptr;
    } catch(const std::bad_alloc& error){
        std::cerr << "LoadImage - Memory allocation error " << error.what() << "\n";
        return nullptr;
    } catch(const std::exception& error){
        std::cerr << "LoadImage - Exception " << error.what() << "\n";
        return nullptr;
    }
}

bool ImageProcessor::saveImage(const std::string& savePath, Image& image){
    try {
        cv::Mat outputMat = image.getFrameCV();
        return cv::imwrite(savePath, outputMat);
    } catch(const std::exception& error){
        std::cerr << "Save Image - Exception " << error.what() << "\n";
        return false;
    }
}