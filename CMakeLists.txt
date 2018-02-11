# Setup project
cmake_minimum_required(VERSION 3.5)
project(TwoCoords VERSION 0.1.0 LANGUAGES CXX)

include(ExternalProject)

# Set compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "enable glfw documentation")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "enable glfw examples")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "enable glfw tests")

# Include libraries
find_package(OpenGL REQUIRED)

include_directories(include)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(thirdparty/spdlog/include)
include_directories(thirdparty/glew/include)

link_directories(${CMAKE_BINARY_DIR}/lib)

# Generate files
configure_file(include/version.h.in ${TwoCoords_BINARY_DIR}/version.h @ONLY)
include_directories("${TwoCoords_BINARY_DIR}")

execute_process(WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/thirdparty/glew" COMMAND make -C auto)

# Include subdirectories
enable_testing()

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glew/build/cmake)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)
