# Create a fake target, to force a target to build, regardless of dependency.
# Taken from https://stackoverflow.com/a/31518137/104370
set(DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD ${CMAKE_CURRENT_BINARY_DIR}/__fake_output_file_to_force_build)

add_subdirectory(doxygen)
add_subdirectory(run_mdsnippets)
add_subdirectory(sphinx)
