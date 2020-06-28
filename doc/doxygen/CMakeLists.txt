# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Only regenerate Doxygen when the Doxyfile or public headers change
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${APPROVAL_TESTS_PUBLIC_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/OverviewForDoxygen.cpp
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating Doxygen docs"
        VERBATIM)

# Nice named target so we can run the job easily
add_custom_target(Doxygen DEPENDS ${DOXYGEN_INDEX_FILE})

# Show where to find the generated documentation
add_custom_command(TARGET Doxygen POST_BUILD
        COMMAND ;
        COMMENT "For Doxygen output, open ${DOXYGEN_INDEX_HTML}"
        )
