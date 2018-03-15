# Add source files
file(GLOB SOURCES "./*.cpp")

# Setup executable
add_executable(TwoCoordsExample ${SOURCES})

# Link libraries
target_link_libraries(TwoCoordsExample TwoCoords)

# Copy assets into build directory
add_custom_command(TARGET TwoCoordsExample
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/example/assets/
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/example/assets/* ${CMAKE_BINARY_DIR}/example/assets/
)
