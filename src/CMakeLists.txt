# Add source files
add_definitions(-DTWOCOORDS_EXPORTS)

file(GLOB SOURCES "./*.cpp")

# Setup library
add_library(TwoCoords SHARED ${SOURCES})

# Link libraries
