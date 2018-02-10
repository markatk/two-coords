# Add library includes
include_directories(../thirdparty/Catch2/single_include)

# Add source files
file(GLOB SOURCES "./*.cpp")

# Setup executable
add_executable(TwoCoordsTest ${SOURCES})

# Link libraries
target_link_libraries(TwoCoordsTest TwoCoords)
