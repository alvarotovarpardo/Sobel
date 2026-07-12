set(CORE_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/filter_selector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/filter_sobel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image_processor.cpp
)

add_library(SobelCore STATIC ${CORE_SRC})

target_include_directories(SobelCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(TARGET opencv::opencv)
    message(STATUS "Core - Linking OpenCV target via Conan")
    target_link_libraries(SobelCore PUBLIC opencv::opencv OpenMP::OpenMP_CXX)
else()
    message(STATUS "Core - OpenCV target via CMake variables")
    target_link_libraries(SobelCore PUBLIC ${OpenCV_LIBS} OpenMP::OpenMP_CXX)
endif()