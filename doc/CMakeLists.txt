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
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

# Doxygen won't create this for us
file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

# Only regenerate Doxygen when the Doxyfile or public headers change
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
        DEPENDS ${APPROVAL_TESTS_PUBLIC_HEADERS} ${CMAKE_CURRENT_SOURCE_DIR}/OverviewForDoxygen.cpp
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
        MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
        COMMENT "Generating docs"
        VERBATIM)

# Nice named target so we can run the job easily
add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

# Only regenerate Sphinx when:
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
        ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
        ${DOXYGEN_INDEX_FILE}
        MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
        COMMENT "Generating documentation with Sphinx")

# Nice named target so we can run the job easily
add_custom_target(Sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})

# Add an install target to install the docs
include(GNUInstallDirs)
install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
