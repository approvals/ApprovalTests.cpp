find_package(Doxygen)
if (NOT Doxygen_FOUND)
    message(STATUS "Doxygen not found: Will not generate docs")
    return()
endif ()
find_package(Sphinx)
if (NOT Sphinx_FOUND)
    message(STATUS "Sphinx not found: Will not generate docs")
    return()
endif ()

# Find all the public headers
set(APPROVAL_TESTS_PUBLIC_HEADER_DIR ${PROJECT_SOURCE_DIR}/ApprovalTests)
file(GLOB_RECURSE APPROVAL_TESTS_PUBLIC_HEADERS CONFIGURE_DEPENDS ${APPROVAL_TESTS_PUBLIC_HEADER_DIR}/*.h)

# Find all the .md files in doc/ directory
# APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES will contain all mdsource/*.source.md files
set(APPROVAL_TESTS_DOC_DIR ${PROJECT_SOURCE_DIR}/doc)
file(GLOB_RECURSE APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES CONFIGURE_DEPENDS ${APPROVAL_TESTS_DOC_DIR}/*.source.md)

# APPROVAL_TESTS_GEN_DOC_MD_FILES        will contain corresponding *.md
string(REPLACE "mdsource/" "" APPROVAL_TESTS_GEN_DOC_MD_FILES "${APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES}")
string(REPLACE ".source.md" ".md" APPROVAL_TESTS_GEN_DOC_MD_FILES "${APPROVAL_TESTS_GEN_DOC_MD_FILES}")

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/ApprovalTests)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYGEN_INDEX_HTML ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYGEN_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/doxygen)
set(DOXYFILE_IN ${DOXYGEN_CONFIG_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_subdirectory(doxygen)

add_subdirectory(run_mdsnippets)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sphinx)
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_subdirectory(sphinx)
