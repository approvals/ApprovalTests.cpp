if (NOT APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION)
    return()
endif()

message(STATUS "Add CPM.cmake")
# download CPM.cmake
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.6/CPM.cmake
        ${CMAKE_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=11c3fa5f1ba14f15d31c2fb63dbc8628ee133d81c8d764caad9a8db9e0bacb07
)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

message(STATUS "Fetching external libraries started")

message(STATUS "Fetching catch2 v3")
CPMAddPackage(
        NAME catch2
        GITHUB_REPOSITORY catchorg/Catch2
        GIT_TAG v3.5.0
)
