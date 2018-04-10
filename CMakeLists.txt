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

set(OpenGL_GL_PREFERENCE GLVND)

# Include libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenAL REQUIRED)

include_directories(include)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(${ALUT_INCLUDE_DIR})
include_directories(thirdparty/spdlog/include)
include_directories(thirdparty/glm)
include_directories(thirdparty/stb)
include_directories(thirdparty/tinydir)

if (NOT APPLE)
    link_directories(${CMAKE_BINARY_DIR}/lib)
endif()

# Generate files
configure_file(include/version.h.in ${TwoCoords_BINARY_DIR}/version.h @ONLY)
include_directories("${TwoCoords_BINARY_DIR}")

execute_process(WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/thirdparty/glew" COMMAND make -C auto)

# Include subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)
