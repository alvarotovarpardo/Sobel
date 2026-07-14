#include "image.h"

Image::Image() : m_iWidth(0), m_iHeight(0), m_iChannels(0) {
}

Image::Image(int width, int height, int channels, const uint8_t* rawData) 
    : m_iWidth(width), m_iHeight(height), m_iChannels(channels) 
{
    size_t imageSize = width * height * channels;

    if (rawData != nullptr && imageSize > 0) {
        matData.assign(rawData, rawData + imageSize);
    }
}