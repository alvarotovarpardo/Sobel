add_library(sobel_native SHARED src/jni_bridge.cpp)

find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(sobel_native 
    PRIVATE 
        SobelCore
        ${log-lib} 
        ${jnigraphics-lib}
)