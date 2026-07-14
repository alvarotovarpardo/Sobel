cmake_minimum_required(VERSION 3.22.1)

project("sobelandroid")

find_package(OpenMP REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${OpenMP_CXX_FLAGS}")

add_subdirectory(../../../../../core core_build)

add_library(${CMAKE_PROJECT_NAME} SHARED
        android_bridge.cpp)

find_library(log-lib log)
find_library(jnigraphics-lib jnigraphics)

target_link_libraries(${CMAKE_PROJECT_NAME}
        SobelCore
        android
        ${log-lib}
        ${jnigraphics-lib}
        OpenMP::OpenMP_CXX)