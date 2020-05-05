# TODO Only regenerate Sphinx when:
# - Doxygen has rerun
# - Our doc files have been updated
# - The Sphinx config has been updated
add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        # Tell Breathe where to find the Doxygen output
        -Dbreathe_projects.ApprovalTests.cpp=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DEPENDS
        # Other docs files you want to track should go here (or in some variable)
        api/approving.rst
        api/core.rst
        index.rst
        markdown_conversion.py
        ${DOXYGEN_INDEX_FILE}
        ${APPROVAL_TESTS_GEN_DOC_MD_FILES}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE} Doxygen)

# If any .source.md files have been changed, rerun mdsnippets
# TODO Also add dependency on files containing any snippets
list(GET APPROVAL_TESTS_GEN_DOC_MD_FILES 0 FIRST_GENERATED_MD_FILE)
add_custom_command(OUTPUT ${FIRST_GENERATED_MD_FILE}
        COMMAND mdsnippets
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS ${APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES}
        BYPRODUCTS ${APPROVAL_TESTS_GEN_DOC_MD_FILES}
        )

# Show where to find the generated documentation
add_custom_command(TARGET Sphinx POST_BUILD
        COMMAND ;
        COMMENT "For Sphinx output, open ${SPHINX_INDEX_FILE}"
        )

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
