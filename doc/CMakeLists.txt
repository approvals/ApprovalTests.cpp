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
file(GLOB_RECURSE APPROVAL_TESTS_PUBLIC_HEADERS ${APPROVAL_TESTS_PUBLIC_HEADER_DIR}/*.h)

set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/ApprovalTests)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYGEN_INDEX_HTML ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_subdirectory(doxygen)

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_subdirectory(sphinx)
