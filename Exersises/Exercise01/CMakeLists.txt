cmake_minimum_required(VERSION 3.0.0)
project(GraphicsExercises01 VERSION 0.1.0 LANGUAGES C CXX)

# Use C++11
set (CMAKE_CXX_STANDARD 11)

# Disable warning related to deprecated functions in the standard library
if(CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Add directories that CMake search in for the header files that we will include  
include_directories(
    vendor/stb
    vendor/glm
)

# Define a list of files that will be compiled with main.cpp and test.cpp
# Note: Header files are not compiled separately, but we still add them to let intellisense know they are part of the project
set(SRC_FILES
    src/color.hpp
    src/color.cpp
    src/image.hpp
    src/image.cpp
    src/rasterize.hpp
    src/rasterize.cpp
)

# Define an executable "rasterizer" that will be built by compiling and linking main.cpp and the source files defined above
add_executable(rasterizer src/main.cpp ${SRC_FILES})

#############################
### Testing Configuration ###
#############################

# Define an executable "tester" that will be built by compiling and linking test.cpp and the source files defined above
# "tester" will be used for testing the code using ctest
add_executable(tester src/test.cpp ${SRC_FILES})

enable_testing()
# Collect a list of the test cases from the folder "tests/scenes"
file(GLOB TEST_CASES ${PROJECT_SOURCE_DIR}/tests/scenes/*.txt)
# For each test case file, we will add a test that will be run via ctest
foreach(TEST_CASE_PATH IN LISTS TEST_CASES)
    get_filename_component(TEST_CASE ${TEST_CASE_PATH} NAME_WLE) # This line gets the test case file name without the extension
    add_test(${TEST_CASE} tester ${PROJECT_SOURCE_DIR}/tests ${TEST_CASE})
endforeach()
