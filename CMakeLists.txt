cmake_minimum_required(VERSION 3.12)

# disable testsuite if used via add_subdirectory()
if (NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
else()
    set(NOT_SUBPROJECT OFF)
endif ()

project(ApprovalTests.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")
include(ApprovalTestsOptions)

if (NOT CYGWIN)
    # cygwin on GitHub Actions gives the following, as of 2022-09-05
    # ccache: error: execute_noreturn of /usr/bin/c++.exe failed: No such file or directory
    include(UseCompilerCache)
    useCompilerCache()
endif ()

#if (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" AND
#        CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftime-trace")
#endif ()

add_subdirectory(ApprovalTests)

set(CMAKE_VERBOSE_MAKEFILE off)

if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif ()

if (NOT_SUBPROJECT)
    # If adding new dependencies here, update:
    #   scripts/clone_dependencies.sh
    #   github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/dev_approvals/
    #   github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/dev_approvals_fetch_content/
    add_subdirectory(CMake/cpputest)
    add_subdirectory(CMake/googletest)
endif ()

# This will optionally add the other third-party sub-directories
add_subdirectory(third_party)
if (APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2V3)
    add_subdirectory(CMake/catch2v3)
endif ()

if (APPROVAL_TESTS_BUILD_TESTING OR APPROVAL_TESTS_BUILD_EXAMPLES)
    enable_testing()
endif ()

if (APPROVAL_TESTS_BUILD_TESTING)
    add_subdirectory(tests)
endif ()

if (APPROVAL_TESTS_BUILD_EXAMPLES)
    add_subdirectory(CMake/filesystem)
    add_subdirectory(CMake/fmt)
    add_subdirectory(examples)
endif ()

if (APPROVAL_TESTS_BUILD_DOCS)
    add_subdirectory(doc)
endif ()

#message("CMAKE_VERSION = ${CMAKE_VERSION}")
#message("CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
#message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
#message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
#message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message("CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
#message("CMAKE_UNITY_BUILD = ${CMAKE_UNITY_BUILD}")
#message("NOT_SUBPROJECT = ${NOT_SUBPROJECT}")
#message("APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2 = ${APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2}")
#message("APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST = ${APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST}")
#message("APPROVAL_TESTS_BUILD_THIRD_PARTY_UT = ${APPROVAL_TESTS_BUILD_THIRD_PARTY_UT}")
#message("APPROVAL_TESTS_BUILD_TESTING = ${APPROVAL_TESTS_BUILD_TESTING}")
#message("APPROVAL_TESTS_BUILD_EXAMPLES = ${APPROVAL_TESTS_BUILD_EXAMPLES}")
#message("APPROVAL_TESTS_BUILD_DOCS = ${APPROVAL_TESTS_BUILD_DOCS}")
#message("APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION = ${APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION}")
#message("APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION = ${APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION}")
#message("APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION = ${APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION}")
#message("APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION = ${APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION}")
#message("APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION = ${APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION}")
#message("APPROVAL_TESTS_ENABLE_UT_INTEGRATION = ${APPROVAL_TESTS_ENABLE_UT_INTEGRATION}")
