# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(Triangles)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Add the include directory for the project
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the subdirectories for the src and test folders
add_subdirectory(src)
add_subdirectory(../third_party ${CMAKE_CURRENT_SOURCE_DIR}/build/third_party)
add_subdirectory(tests)