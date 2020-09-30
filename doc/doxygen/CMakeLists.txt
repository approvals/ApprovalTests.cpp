find_package(Doxygen)
if (NOT Doxygen_FOUND)
    message(STATUS "Doxygen not found: Will not generate docs")
    return()
endif ()

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/ApprovalTests)
set(DOXYGEN_INPUT_DIR ${DOXYGEN_INPUT_DIR} PARENT_SCOPE)

set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(DOXYGEN_OUTPUT_DIR ${DOXYGEN_OUTPUT_DIR} PARENT_SCOPE)

set(DOXYGEN_INDEX_HTML ${DOXYGEN_OUTPUT_DIR}/html/index.html)

set(DOXYGEN_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(DOXYGEN_CONFIG_DIR ${DOXYGEN_CONFIG_DIR} PARENT_SCOPE)

set(DOXYFILE_IN ${DOXYGEN_CONFIG_DIR}/Doxyfile.in)
set(DOXYFILE_IN ${DOXYFILE_IN} PARENT_SCOPE)

set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXYFILE_OUT ${DOXYFILE_OUT} PARENT_SCOPE)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Only regenerate Doxygen when the Doxyfile, documentation or public headers change
add_custom_command(OUTPUT ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD}
        DEPENDS
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating Doxygen docs"
        VERBATIM)

# Nice named target so we can run the job easily
add_custom_target(Doxygen DEPENDS ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD})

# Show where to find the generated documentation
add_custom_command(TARGET Doxygen POST_BUILD
        COMMAND ;
        COMMENT "For Doxygen output, open ${DOXYGEN_INDEX_HTML}"
        )
