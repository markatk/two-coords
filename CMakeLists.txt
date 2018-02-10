# Setup project
cmake_minimum_required(VERSION 3.5)
project(TwoCoords VERSION 0.1.0 LANGUAGES CXX)

include(ExternalProject)

# Set compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include libraries
include_directories(include)

include_directories(thirdparty/spdlog/include)
include_directories(thirdparty/glew/include)

# Generate files
configure_file(include/version.h.in ${TwoCoords_BINARY_DIR}/version.h @ONLY)
include_directories("${TwoCoords_BINARY_DIR}")

# Include subdirectories
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(example)

add_subdirectory(thirdparty/glfw)

# Add external projects
ExternalProject_Add(getglew
  SOURCE_DIR ${TwoCoords_SOURCE_DIR}/thirdparty/glew
  CONFIGURE_COMMAND make -C auto && cd build && cmake ./cmake -DCMAKE_INSTALL_PREFIX=${TwoCoords_BINARY_DIR}
  INSTALL_COMMAND ""
  BUILD_IN_SOURCE 1
)
