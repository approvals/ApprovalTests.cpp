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

# Find all the public source
file(GLOB_RECURSE APPROVAL_TESTS_PUBLIC_SOURCE CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/ApprovalTests/*.h
        ${PROJECT_SOURCE_DIR}/ApprovalTests/*.cpp)

# Find all the .md files in doc/ directory
# APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES will contain all mdsource/*.source.md files
file(GLOB_RECURSE APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/doc/*.source.md)

# APPROVAL_TESTS_GEN_DOC_MD_FILES        will contain corresponding *.md
string(REPLACE "mdsource/" "" APPROVAL_TESTS_GEN_DOC_MD_FILES "${APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES}")
string(REPLACE ".source.md" ".md" APPROVAL_TESTS_GEN_DOC_MD_FILES "${APPROVAL_TESTS_GEN_DOC_MD_FILES}")

add_subdirectory(doxygen)

add_subdirectory(run_mdsnippets)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/sphinx)
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_subdirectory(sphinx)
