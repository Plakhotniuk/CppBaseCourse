enable_testing()

file(GLOB_RECURSE TEST_SOURCES gtest_*.cpp *.hpp *.h *.cc)
SET(LIBS gtest_main hw3d hwc)
add_definitions(-DPROJECT_DIR_RAW="${PROJECT_SOURCE_DIR}")

foreach(TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
    target_link_libraries(${EXECUTABLE_NAME} ${LIBS})
    message("TEST_FILE: ${TEST_FILE}")
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()
