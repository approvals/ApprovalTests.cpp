find_package(Doxygen)
if (NOT Doxygen_FOUND)
    message(STATUS "Doxygen not found: Will not generate docs")
    return()
endif ()

# Note that DOXYGEN_INPUT_DIR appears to be unused,
# but is actually referenced inside Doxyfile.in.
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/ApprovalTests)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
# Add to parent scope, as this is used by the Sphinx target
set(DOXYGEN_OUTPUT_DIR ${DOXYGEN_OUTPUT_DIR} PARENT_SCOPE)

set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

set(DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD ${CMAKE_CURRENT_BINARY_DIR}/__fake_output_file_to_force_build)

add_custom_command(OUTPUT ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        COMMENT "Generating Doxygen docs"
        VERBATIM)

# Nice named target so we can run the job easily
add_custom_target(Doxygen DEPENDS ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD})

# Show where to find the generated documentation
add_custom_command(TARGET Doxygen POST_BUILD
        COMMAND ;
        COMMENT "For Doxygen output, open ${DOXYGEN_OUTPUT_DIR}/html/index.html"
        )
