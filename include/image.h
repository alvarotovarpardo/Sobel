#pragma once
#include <vector>
#include <filesystem>
#include <opencv2/opencv.hpp>

class Image {
public:
    Image() : m_iWidth(0), m_iHeight(0), m_iChannels(0) {}

protected:
    int getWidth  {return m_iWidth; };
    int getHeight {return m_iHeight;};
    int getChannels {return m_iChannels;};
    void setWidth(int iWidth){m_iWidth = iWidth;};
    void setHeight(int iHeight){m_iHeight = iHeight;};
    void setChannels(int iChannels){m_iChannels = iChannels;};

private:
    int m_iWidth;
    int m_iHeight;
    int m_iChannels;    
};