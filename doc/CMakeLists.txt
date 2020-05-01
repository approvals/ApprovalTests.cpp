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
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) #Doxygen won't create this for us
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${APPROVAL_TESTS_PUBLIC_HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/OverviewForDoxygen.cpp
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT " Generating docs ")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/docs/sphinx)

add_custom_target(Sphinx ALL
        COMMAND
        ${SPHINX_EXECUTABLE} -b html
        -Dbreathe_projects.ApprovalTests.cpp=${DOXYGEN_OUTPUT_DIR}/xml
        ${SPHINX_SOURCE} ${SPHINX_BUILD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Sphinx")
