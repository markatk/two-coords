# Setup project
cmake_minimum_required(VERSION 3.5)
project(TwoCoords VERSION 0.1.0 LANGUAGES CXX)

# Set compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include libraries
include_directories(include)

include_directories(thirdparty/spdlog/include)

# Generate files
configure_file(include/version.h.in ${TwoCoords_BINARY_DIR}/version.h @ONLY)
include_directories("${TwoCoords_BINARY_DIR}")

# Include subdirectories
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)

add_subdirectory(thirdparty/glfw)
