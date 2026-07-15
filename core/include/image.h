#pragma once
#include <vector>
#include <filesystem>
#include "logger.h"

class Image {
public:
    Image();
    Image(int width, int height, int channels, const uint8_t* matdata);

    const std::vector<uint8_t>& getFrameData() const { return matData; }

    int getWidth()  {return m_iWidth; }
    int getHeight() {return m_iHeight;}
    int getChannels() {return m_iChannels;}
    void setWidth(int iWidth){m_iWidth = iWidth;}
    void setHeight(int iHeight){m_iHeight = iHeight;}
    void setChannels(int iChannels){m_iChannels = iChannels;}
    void resize(size_t size) { matData.resize(size); }
    std::vector<uint8_t> matData;
private:
    int m_iWidth;
    int m_iHeight;
    int m_iChannels;
};