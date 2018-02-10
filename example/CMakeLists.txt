# Add source files
file(GLOB SOURCES "./*.cpp")

# Setup executable
add_executable(TwoCoordsExample ${SOURCES})

# Link libraries
target_link_libraries(TwoCoordsExample TwoCoords)