#include "filter_sobel.h"

Image FilterSobel::applyFilter(const Image& inputImage)
{
    Image outputImage = inputImage;
    int iWidth = const_cast<Image&>(inputImage).getWidth();
    int iHeight = const_cast<Image&>(inputImage).getHeight();
    int iChannels = const_cast<Image&>(inputImage).getChannels();

    const uint8_t* inputData = inputImage.getFrameData().data();
    uint8_t* outputData = outputImage.matData.data();

    #pragma omp parallel for
    for (int y = 1; y < iHeight - 1; ++y) {
        for (int x = 1; x < iWidth - 1; ++x) {
            for (int c = 0; c < iChannels; ++c) {
                int gx = 0;
                int gy = 0;

                gx += inputData[((y - 1) * iWidth + (x - 1)) * iChannels + c] * -1;
                gx += inputData[((y - 1) * iWidth + (x + 1)) * iChannels + c] * 1;
                gx += inputData[(y * iWidth + (x - 1)) * iChannels + c] * -2;
                gx += inputData[(y * iWidth + (x + 1)) * iChannels + c] * 2;
                gx += inputData[((y + 1) * iWidth + (x - 1)) * iChannels + c] * -1;
                gx += inputData[((y + 1) * iWidth + (x + 1)) * iChannels + c] * 1;

                gy += inputData[((y - 1) * iWidth + (x - 1)) * iChannels + c] * -1;
                gy += inputData[((y - 1) * iWidth + x) * iChannels + c] * -2;
                gy += inputData[((y - 1) * iWidth + (x + 1)) * iChannels + c] * -1;
                gy += inputData[((y + 1) * iWidth + (x - 1)) * iChannels + c] * 1;
                gy += inputData[((y + 1) * iWidth + x) * iChannels + c] * 2;
                gy += inputData[((y + 1) * iWidth + (x + 1)) * iChannels + c] * 1;

                int magnitude = static_cast<int>(std::sqrt(gx * gx + gy * gy));
                magnitude = std::min(255, std::max(0, magnitude));

                outputData[(y * iWidth + x) * iChannels + c] = static_cast<uint8_t>(magnitude);
            }
        }
    }

    return outputImage;
}