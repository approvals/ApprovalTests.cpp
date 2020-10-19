find_package(Sphinx)
if (NOT Sphinx_FOUND)
    message(STATUS "Sphinx not found: Will not generate docs")
    return()
endif ()

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR})
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

set(DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD ${CMAKE_CURRENT_BINARY_DIR}/__fake_output_file_to_force_build)

add_custom_command(OUTPUT ${SPHINX_INDEX_FILE} ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD}
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        # Tell Breathe where to find the Doxygen output
        -Dbreathe_projects.ApprovalTests.cpp=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx DEPENDS Doxygen RunMdsnippets ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD})

# Show where to find the generated documentation
add_custom_command(TARGET Sphinx POST_BUILD
        COMMAND ;
        COMMENT "For Sphinx output, open ${SPHINX_INDEX_FILE}"
        )

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
