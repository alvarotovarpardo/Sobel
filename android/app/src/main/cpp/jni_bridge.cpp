#include <jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <cstring>

// Incluimos tus cabeceras del Core
#include "image.h"
#include "filter_sobel.h"

// Macro para usar el Log de Android en C++ (aparecerá en el Logcat de Android Studio)
#define LOG_TAG "SobelJNI"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" {

// ¡ATENCIÓN AL NOMBRE DE LA FUNCIÓN!
// JNI es muy estricto con esto. El formato es: Java_paquete_Clase_metodo
// Si tu app en Android se llama "com.example.sobelapp" y llamas a esto desde "MainActivity", 
// el nombre debe ser Java_com_example_sobelapp_MainActivity_applySobelNative
JNIEXPORT void JNICALL
Java_com_example_sobelapp_MainActivity_applySobelNative(
        JNIEnv* env, 
        jobject /* this */, 
        jobject bitmap) {
    
    AndroidBitmapInfo info;
    void* pixels;
    int ret;

    // 1. Obtener información del Bitmap (ancho, alto, formato)
    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGE("Error en AndroidBitmap_getInfo() ! error=%d", ret);
        return;
    }

    // Asegurarnos de que la imagen es RGBA_8888 (4 canales, 8 bits por canal)
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Formato de Bitmap no soportado. Debe ser RGBA_8888.");
        return;
    }

    // 2. Bloquear los píxeles para acceder a la memoria de Java desde C++
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, &pixels)) < 0) {
        LOGE("Error en AndroidBitmap_lockPixels() ! error=%d", ret);
        return;
    }

    LOGI("Procesando imagen de %dx%d", info.width, info.height);

    // 3. Crear el objeto Image de tu Core
    // Adaptamos el puntero 'pixels' crudo a la estructura que tu código espera.
    // Asumiendo que tu clase Image puede construirse/cargarse con dimensiones y datos crudos:
    // (Si tu clase Image usa cv::Mat por debajo, puedes inicializar cv::Mat con estos datos)
    
    /* EJEMPLO DE ADAPTACIÓN (Ajústalo a los constructores de tu clase Image):
       cv::Mat imgMat(info.height, info.width, CV_8UC4, pixels);
       Image myInputImage(imgMat); 
    */
    
    // Supongamos que tu clase tiene un constructor que recibe datos:
    Image inputImage; 
    // ... [Aquí inyectas 'pixels', 'info.width' y 'info.height' en inputImage] ...

    // 4. Aplicar tu filtro (¡Aquí actúa OpenMP automáticamente!)
    FilterSobel sobelFilter;
    Image outputImage = sobelFilter.applyFilter(inputImage);

    // 5. Copiar el resultado de vuelta al Bitmap de Android
    // outputImage.getFrameData().data() tiene el resultado de tu filtro
    const uint8_t* resultData = outputImage.getFrameData().data();
    
    // El tamaño total en bytes es: Ancho * Alto * 4 (RGBA)
    size_t totalBytes = info.width * info.height * 4;
    std::memcpy(pixels, resultData, totalBytes);

    // 6. Desbloquear los píxeles (Devolver el control a Java)
    AndroidBitmap_unlockPixels(env, bitmap);
    
    LOGI("Filtro Sobel aplicado correctamente en Android.");
}

} // extern "C"