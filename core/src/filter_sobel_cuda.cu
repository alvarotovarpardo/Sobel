#include "filter_sobel_cuda.h"
#include <cuda_runtime.h>

__global__ void sobelFilterKernel(const uint8_t* inputData, uint8_t* outputData, int iWidth, int iHeight, int iChannels){
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    for (int y = 1; y < iHeight - 1; ++y) {
        rowsPerThread[threadID]++;
        for (int x = 1; x < iWidth - 1; ++x) {
            for (int c = 0; c < iChannels; ++c) {
                if(c == 3) {
                    outputData[(y * iWidth + x) * iChannels + c] = inputData[(y * iWidth + x) * iChannels + c];
                    continue;
                }
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
}

Image FilterSobelCuda::applyFilter(const Image& inputImage){
    LOG(INFO) << "Applying Sobel filter using CUDA...";
    Image outputImage = inputImage;

    int iWidth = const_cast<Image&>(inputImage).getWidth();
    int iHeight = const_cast<Image&>(inputImage).getHeight();
    int iChannels = const_cast<Image&>(inputImage).getChannels();
    size_t imageSize = iWidth * iHeight * iChannels * sizeof(uint8_t);

    uint8_t* d_inputData;
    uint8_t* d_outputData;

    cudaMalloc(&d_inputData, imageSize);
    cudaMalloc(&d_outputData, imageSize);

    cudaMemcpy(d_inputData, inputImage.getFrameData().getData(), imageSize, cudaMemcpyHostToDevice);

    dim3 threadsPerBlock(16, 16);
    dim3 numBlocks((iWidth + threadsPerBlock.x - 1) / threadsPerBlock.x, (iHeight + threadsPerBlock.y - 1) / threadsPerBlock.y);
    sobelFilterKernel<<<numBlocks, threadsPerBlock>>>(d_inputData, d_outputData, iWidth, iHeight, iChannels);
    cudaDeviceSynchronize();
    
    cudaMemcpy(outputImage.getFrameData().getData(), d_outputData, imageSize, cudaMemcpyDeviceToHost);

    cudaFree(d_inputData);
    cudaFree(d_outputData);

    return outputImage;
}