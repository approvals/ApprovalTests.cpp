set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR})
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# APPROVAL_TESTS_GEN_DOC_RST_FILES       will contain .rst files corresponding to the generated *.md
string(REPLACE "/doc/" "/doc/sphinx/generated_docs/" APPROVAL_TESTS_GEN_DOC_RST_FILES "${APPROVAL_TESTS_GEN_DOC_MD_FILES}")
string(REPLACE ".md" ".rst" APPROVAL_TESTS_GEN_DOC_RST_FILES "${APPROVAL_TESTS_GEN_DOC_RST_FILES}")

file(GLOB
        APPROVAL_TESTS_SPHINX_TEMPLATE_FILES
        CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/_templates/*
        )

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
        ${APPROVAL_TESTS_SPHINX_TEMPLATE_FILES}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        BYPRODUCTS ${APPROVAL_TESTS_GEN_DOC_RST_FILES}
        COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx DEPENDS ${SPHINX_INDEX_FILE} Doxygen RunMdsnippets)

# Show where to find the generated documentation
add_custom_command(TARGET Sphinx POST_BUILD
        COMMAND ;
        COMMENT "For Sphinx output, open ${SPHINX_INDEX_FILE}"
        )

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
