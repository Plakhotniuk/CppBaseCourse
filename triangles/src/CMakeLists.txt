# src/CMakeLists.txt
file(GLOB_RECURSE SOURCES "*.cpp")

# Create a library from the source files
add_library(Triangles ${SOURCES})
target_include_directories(Triangles PUBLIC ${PROJECT_SOURCE_DIR}/include/..)