cmake_minimum_required(VERSION 3.10)
project(Sobel)

cmake_policy(SET CMP0091 NEW)
message(STATUS "Policy CMP0091 set NEW")
if(EXISTS "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")
    include("${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")
endif()
add_compile_options(-w)

if(WIN32)
    message(STATUS "Setting environment for Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
    if(NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake" CACHE STRING "Toolchain file")
    endif()
    message(STATUS "Setting environment for Unix/Linux")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Release" FORCE)
endif()

set(TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake" CACHE STRING "Toolchain file")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

message("SRC_DIR: ${SRC_DIR}")


set(SOURCES
    ${SRC_DIR}/main.cpp
)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")


find_path(OpenCV_INCLUDE_DIR
    NAMES opencv2/opencv.hpp
    PATHS ${OpenCV_PKGCONF_INCLUDE_DIRS}
)

# message("Conan Include Dirs: ${CONAN_INCLUDE_DIRS}")
find_package(OpenCV REQUIRED)

# if(DEFINED LibRef)
#     message(STATUS "Compiling with LibRef: ${LibRef}")

#     if(LibRef STREQUAL "libAravis")
#         add_subdirectory(Libs/libaravis)
#         target_compile_definitions(${PROJECT_NAME} PUBLIC USE_PLUGIN)
#         target_link_libraries(${PROJECT_NAME} PUBLIC libAravis)

#     endif()
# endif()

include_directories(${FOLDER_DIR})
# add_executable(${PROJECT_NAME} src/main.cpp ../SensiaNuc.cpp ../pixel_manager.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CONAN_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CONAN_LIBS} ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)