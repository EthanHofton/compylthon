# Create a custom target to copy files
# add_custom_command(
#     TARGET cpy_res  # Specify the target that depends on this command
#     POST_BUILD              # Run this command after the build step
#     COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
#     COMMENT "Copying res directory to build directory"
# )

# create a custom command to copy files every time
add_custom_target(cpy_res ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Copying res directory to build directory"
    VERBATIM
)
