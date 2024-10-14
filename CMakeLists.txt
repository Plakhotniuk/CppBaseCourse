cmake_minimum_required(VERSION 3.15)
project(CppBaseCourse)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(third_party)
