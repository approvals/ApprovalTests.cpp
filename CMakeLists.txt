cmake_minimum_required(VERSION 3.8)

# disable testsuite if used via add_subdirectory()
if(NOT DEFINED PROJECT_NAME)
    set(NOT_SUBPROJECT ON)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(ApprovalTests.cpp)
add_subdirectory(ApprovalTests)

set(CMAKE_VERBOSE_MAKEFILE off)

option(APPROVAL_TESTS_ENABLE_CODE_COVERAGE "Enable coverage reporting for selected tests" OFF)
option(APPROVAL_TESTS_ENABLE_CMAKE_INTEGRATION_TESTS "Enable tests that check our CMake integration" ON)

if(APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    message(STATUS "Enable Code Coverage")
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

if (NOT_SUBPROJECT)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                     "${CMAKE_BINARY_DIR}/googletest-build")

    enable_testing()
    add_subdirectory(third_party)
    add_subdirectory(tests)
    add_subdirectory(examples)
endif()

message("CMAKE_VERSION = ${CMAKE_VERSION}")
message("CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message("CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message("CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message("CMAKE_UNITY_BUILD = ${CMAKE_UNITY_BUILD}")
