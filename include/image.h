#pragma once
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>

class Image {
public:
    Image();
    
    const std::vector<uint8_t>& getFrameData() const { return matData; }
    const cv::Mat getCVFrame() { return cv::Mat(m_iHeight, m_iWidth, CV_8UC(m_iChannels), matData.data()); }

protected:
    int getWidth()  {return m_iWidth; };
    int getHeight() {return m_iHeight;};
    int getChannels() {return m_iChannels;};
    void setWidth(int iWidth){m_iWidth = iWidth;};
    void setHeight(int iHeight){m_iHeight = iHeight;};
    void setChannels(int iChannels){m_iChannels = iChannels;};
    std::vector<uint8_t> matData;
private:
    int m_iWidth;
    int m_iHeight;
    int m_iChannels;
        
};