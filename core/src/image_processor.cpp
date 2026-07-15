#include "image_processor.h"
#ifndef __ANDROID__

std::unique_ptr<Image> ImageProcessor::loadImage(const std::string& imagePath){
    
    try {
        cv::Mat readMat = cv::imread(imagePath, cv::IMREAD_UNCHANGED);

        if(readMat.empty()){
            throw std::runtime_error("Image could not be loaded.");
            LOG("Error - Image could not be loaded.");
        }

        std::unique_ptr<Image> pImage = std::make_unique<Image>();
        pImage->setWidth(readMat.cols);
        pImage->setHeight(readMat.rows);
        pImage->setChannels(readMat.channels());
        
        size_t imageMemSize = readMat.total() * readMat.elemSize();
        pImage->resize(imageMemSize);
        std::memcpy(pImage->matData.data(), readMat.ptr(), imageMemSize);
        LOG("Image loaded successfully.");
        return pImage;
    } catch(const cv::Exception& error){
        std::cerr << "LoadImage - Load error " << error.what() << "\n";
        LOG(std::string("Error - Load error ") + error.what());
        return nullptr;
    } catch(const std::bad_alloc& error){
        std::cerr << "LoadImage - Memory allocation error " << error.what() << "\n";
        LOG(std::string("Error - Memory allocation error ") + error.what());
        return nullptr;
    } catch(const std::exception& error){
        std::cerr << "LoadImage - Exception " << error.what() << "\n";
        LOG(std::string("Error - ") + error.what());
        return nullptr;
    }
}

bool ImageProcessor::saveImage(const std::string& savePath, Image& image){
    try {
        const std::vector<uint8_t>& imageData = image.getFrameData();
        cv::Mat outputMat(image.getHeight(), image.getWidth(), CV_8UC3, const_cast<uint8_t*>(imageData.data()));
        LOG("Image saved successfully");
        return cv::imwrite(savePath, outputMat);
    } catch(const std::exception& error){
        std::cerr << "Save Image - Exception " << error.what() << "\n";
        LOG(std::string("Error - ") + error.what());
        return false;
    }
}

#endif // !__ANDROID__