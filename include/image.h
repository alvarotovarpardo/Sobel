#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class Image {
public:
    Image() : m_iWidth(0), m_iHeight(0), m_iChannels(0) {}

private:
    int m_iWidth;
    int m_iHeight;
    int m_iChannels;
    std::vector<uint8_t> data;
};