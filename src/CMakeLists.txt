# Add source files
add_definitions(-DTWOCOORDS_EXPORTS)

file(GLOB SOURCES "./*.cpp")

# Setup library
add_library(TwoCoords SHARED ${SOURCES})

# Link libraries
target_link_libraries(TwoCoords ${OPENGL_LIBRARIES})
target_link_libraries(TwoCoords glfw)
target_link_libraries(TwoCoords GLEW)
target_link_libraries(TwoCoords ${OPENAL_LIBRARY})
target_link_libraries(TwoCoords alut)
target_link_libraries(TwoCoords ${FREETYPE_LIBRARIES})