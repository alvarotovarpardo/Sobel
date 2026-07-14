#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <cstring>

#include "image.h"
#include "filter_sobel.h"

#define LOG_TAG "SobelJNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_sobelandroid_MainActivity_applySobelNative(
        JNIEnv* env,
        jobject /* this */,
        jobject bitmap) {

    AndroidBitmapInfo info;
    void* pixels;
    int ret;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed! error=%d", ret);
        return;
    }

    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format not supported. Must be RGBA_8888.");
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed! error=%d", ret);
        return;
    }

    LOGI("Processing image: %dx%d", info.width, info.height);

    Image inputImage(info.width, info.height, 4, static_cast<uint8_t*>(pixels));

    FilterSobel sobelFilter;
    Image outputImage = sobelFilter.applyFilter(inputImage);

    const uint8_t* resultData = outputImage.getFrameData().data();
    size_t totalBytes = info.width * info.height * 4;
    
    std::memcpy(pixels, resultData, totalBytes);

    AndroidBitmap_unlockPixels(env, bitmap);

    LOGI("Sobel filter applied successfully.");
}

} // extern "C"