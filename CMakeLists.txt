cmake_minimum_required(VERSION 3.8)

# disable testsuite if used via add_subdirectory()
if (NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
endif ()

project(ApprovalTests.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")
include(ApprovalTestsOptions)
include(UseCompilerCache)

if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" AND
        CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftime-trace")
endif ()

useCompilerCache()

add_subdirectory(ApprovalTests)

set(CMAKE_VERBOSE_MAKEFILE off)

if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif ()

if (NOT_SUBPROJECT)
    add_subdirectory(CMake/googletest)
endif ()

# This will optionally add the other third-party sub-directories
add_subdirectory(third_party)

if (NOT_SUBPROJECT OR APPROVAL_TESTS_BUILD_TESTING OR APPROVAL_TESTS_BUILD_EXAMPLES)
    enable_testing()
endif ()

if (NOT_SUBPROJECT OR APPROVAL_TESTS_BUILD_TESTING)
    add_subdirectory(CMake/fmt)
    add_subdirectory(tests)
endif ()

if (NOT_SUBPROJECT OR APPROVAL_TESTS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (NOT_SUBPROJECT OR APPROVAL_TESTS_BUILD_DOCS)
    add_subdirectory(doc)
endif ()

#message("CMAKE_VERSION = ${CMAKE_VERSION}")
#message("CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
#message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
#message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
#message("CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
#message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
#message("CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
#message("CMAKE_UNITY_BUILD = ${CMAKE_UNITY_BUILD}")
#message("APPROVAL_TESTS_BUILD_THIRD_PARTY = ${APPROVAL_TESTS_BUILD_THIRD_PARTY}")
#message("APPROVAL_TESTS_BUILD_TESTING = ${APPROVAL_TESTS_BUILD_TESTING}")
#message("APPROVAL_TESTS_BUILD_EXAMPLES = ${APPROVAL_TESTS_BUILD_EXAMPLES}")
