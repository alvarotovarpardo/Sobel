cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0091 NEW)
message(STATUS "Policy CMP0091 set NEW")

option(CONAN_PACKAGE "Flag ON if is Conan package" OFF)
option(BUILD_CLI "Build the command line interface" ON)
option(BUILD_ANDROID "Build the Android application" OFF)
option(BUILD_QT "Build the Qt application" OFF)

if(WIN32)
    message(STATUS "Setting environment for Windows")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options("/utf-8")
    if(NOT CMAKE_TOOLCHAIN_FILE)
        if(NOT CMAKE_BUILD_TYPE)
            execute_process(
                COMMAND conan profile path default
                OUTPUT_VARIABLE CONAN_PROFILE_PATH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            if(EXISTS "${CONAN_PROFILE_PATH}")
                file(STRINGS "${CONAN_PROFILE_PATH}" CONAN_BUILD_TYPE_LINE REGEX "^build_type=")
                string(REPLACE "build_type=" "" CMAKE_BUILD_TYPE "${CONAN_BUILD_TYPE_LINE}")
                message(STATUS "Detected Conan build type: ${CMAKE_BUILD_TYPE}")
            else()
                set(CMAKE_BUILD_TYPE "Release")
            endif()
        endif()
        if(NOT CONAN_PACKAGE)
        IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")
        message(STATUS "Running Conan install...")
        execute_process(
            COMMAND  conan install . --build=missing -r conancenter -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=true -s build_type=${CMAKE_BUILD_TYPE} --output-folder=build/${CMAKE_BUILD_TYPE} -c tools.cmake.cmake_layout:build_folder=.
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE CONAN_RESULT
        )
        endif()
        get_filename_component(TOOLCHAIN_PATH2
            "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake"
            ABSOLUTE
        )
        message(STATUS "Searching Conan Toolchain at: ${TOOLCHAIN_PATH2}")
            if(EXISTS ${TOOLCHAIN_PATH2})
                set ( CMAKE_TOOLCHAIN_FILE_SOBEL ${TOOLCHAIN_PATH2})
                include(${TOOLCHAIN_PATH2})
            else()
                message(WARNING "conan_toolchain.cmake not found at ${TOOLCHAIN_PATH2}")
            endif()
        else()
            message("Sobel compiling for package")
            get_filename_component(TOOLCHAIN_PATH2 "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake" ABSOLUTE)
            include(${TOOLCHAIN_PATH2})
        endif()
    endif()
elseif(UNIX)
    message(STATUS "Setting environment for UNIX")
    if(NOT CMAKE_TOOLCHAIN_FILE)
        if(NOT CMAKE_BUILD_TYPE)
            execute_process(
                COMMAND conan profile path default
                OUTPUT_VARIABLE CONAN_PROFILE_PATH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            if(EXISTS "${CONAN_PROFILE_PATH}")
                file(STRINGS "${CONAN_PROFILE_PATH}" CONAN_BUILD_TYPE_LINE REGEX "^build_type=")
                string(REPLACE "build_type=" "" CMAKE_BUILD_TYPE "${CONAN_BUILD_TYPE_LINE}")
                message(STATUS "Detected Conan build type: ${CMAKE_BUILD_TYPE}")
            else()
                set(CMAKE_BUILD_TYPE "Release")
            endif()
        endif()
        if(NOT CONAN_PACKAGE)
        IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")
        message(STATUS "Running Conan install...")
        execute_process(
            COMMAND  conan install . --build=missing -r conancenter -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=true -s build_type=${CMAKE_BUILD_TYPE} --output-folder=build/${CMAKE_BUILD_TYPE} -c tools.cmake.cmake_layout:build_folder=.
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE CONAN_RESULT
        )
        endif()
        get_filename_component(TOOLCHAIN_PATH2
            "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake"
            ABSOLUTE
        )
        message(STATUS "Searching Conan Toolchain at: ${TOOLCHAIN_PATH2}")
            if(EXISTS ${TOOLCHAIN_PATH2})
                set ( CMAKE_TOOLCHAIN_FILE_SOBEL ${TOOLCHAIN_PATH2})
                include(${TOOLCHAIN_PATH2})
            else()
                message(WARNING "conan_toolchain.cmake not found at ${TOOLCHAIN_PATH2}")
            endif()
        else()
            message("Sobel compiling for package")
            get_filename_component(TOOLCHAIN_PATH2 "${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake" ABSOLUTE)
            include(${TOOLCHAIN_PATH2})
        endif()
    endif()
endif()

project(Sobel CXX CUDA)

set(TOOLCHAIN_FILE "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake" CACHE STRING "Toolchain file")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

find_path(OpenCV_INCLUDE_DIR
    NAMES opencv2/opencv.hpp
    PATHS ${OpenCV_PKGCONF_INCLUDE_DIRS}
)

find_package(OpenCV REQUIRED CONFIG)

if(APPLE)
    set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
    set(OpenMP_CXX_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
endif()
find_package(OpenMP REQUIRED)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


message("SRC_DIR: ${SRC_DIR}")


add_subdirectory(core)

if(BUILD_CLI)
    add_subdirectory(cli)
endif()

if(BUILD_QT)
    add_subdirectory(qt)
endif()

if(BUILD_ANDROID)
    add_subdirectory(android)
endif()

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/media/ DESTINATION media/)

include(CPack)