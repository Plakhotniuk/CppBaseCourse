# include, source directories
set(MYLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MYLIB_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE MYLIB_HEADERS "${MYLIB_INCLUDE_DIR}/*.hpp" "${MYLIB_INCLUDE_DIR}/*.h")
file(GLOB_RECURSE MYLIB_SOURCES "${MYLIB_SRC_DIR}/*.cpp")

add_library(HomeTasks STATIC ${MYLIB_SOURCES} ${MYLIB_HEADERS})

target_include_directories(HomeTasks PUBLIC "${MYLIB_INCLUDE_DIR}")

target_compile_features(HomeTasks PRIVATE cxx_std_23)