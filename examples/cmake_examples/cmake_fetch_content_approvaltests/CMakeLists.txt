cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
# This version is needed for FetchContent_Declare & FetchContent_MakeAvailable

project(cmake_fetch_content_approvaltests)

include(FetchContent)
if (NOT TARGET ApprovalTests)
    FetchContent_Declare(ApprovalTests
            GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
            GIT_TAG cmake_docs)
    set(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2 ON CACHE BOOL "")
    FetchContent_MakeAvailable(ApprovalTests)
endif ()

enable_testing()

add_subdirectory(cmake_fetch_content_approvaltests_tests)
