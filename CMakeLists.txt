cmake_minimum_required(VERSION 3.15)
project(CppBaseCourse VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

add_library(hwc INTERFACE)
target_include_directories(hwc INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(hwc INTERFACE cxx_std_23)


add_library(hw3d INTERFACE)
target_include_directories(hw3d INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(hw3d INTERFACE cxx_std_23)

add_subdirectory(tests)

add_subdirectory(third_party)