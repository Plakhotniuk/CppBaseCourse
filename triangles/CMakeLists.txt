cmake_minimum_required(VERSION 3.10)
project(Triangles)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

enable_testing()

set(SRC src/Triangles3D.cpp)

add_library(TrianglesLib STATIC ${SRC})

target_include_directories(TrianglesLib PUBLIC "include")

add_subdirectory(../third_party ${CMAKE_CURRENT_SOURCE_DIR}/build/third_party)
add_subdirectory(tests)