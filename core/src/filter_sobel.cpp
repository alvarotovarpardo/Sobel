#include "filter_sobel.h"

Image FilterSobel::applyFilter(const Image& inputImage)
{
    LOG("Applying Filter Sobel...");
    Image outputImage = inputImage;
    int iWidth = const_cast<Image&>(inputImage).getWidth();
    int iHeight = const_cast<Image&>(inputImage).getHeight();
    int iChannels = const_cast<Image&>(inputImage).getChannels();

    const uint8_t* inputData = inputImage.getFrameData().data();
    uint8_t* outputData = outputImage.matData.data();
    int maxNumThreads = omp_get_max_threads();
    LOG(std::to_string(maxNumThreads) + std::string(" number of threads available."));

    std::vector<int> rowsPerThread(maxNumThreads, 0);

    double startTime = omp_get_wtime();
    #pragma omp parallel default(none) shared(iWidth, iHeight, iChannels, inputData, outputData, rowsPerThread)
    {
        int threadID = omp_get_thread_num();
        #pragma omp single
        { 
            LOG(std::to_string(omp_get_num_threads()) + std::string(" threads on execution."));
        }
        
        #pragma omp parallel for schedule(static)
        for (int y = 1; y < iHeight - 1; ++y) {
            rowsPerThread[threadID]++;
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
    }
    double endTime = omp_get_wtime();
    double totalTime = endTime - startTime;
    std::string msg = "Sobel Algorithm ended. Execution time: " + std::to_string(totalTime) + " ms for " + std::to_string(iWidth) + "x" + std::to_string(iHeight) + " pixels processed.";
    LOG(msg);
    for(int i = 0; i < maxNumThreads; ++i){
        if(rowsPerThread[i] > 0){
            std::string msg = "Thread " + std::to_string(i) + " processed " + std::to_string(rowsPerThread[i]) + " rows.";
            LOG(msg);
        }
    }

    return outputImage;
}