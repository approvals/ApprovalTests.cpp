option(APPROVAL_TESTS_ENABLE_CODE_COVERAGE "Enable coverage reporting for selected tests" OFF)

option(APPROVAL_TESTS_BUILD_CMAKE_INTEGRATION_TESTING "Enable tests that check our CMake integration" OFF)

# Control which of our copies/downloads of third_party libraries are made available
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_GOOGLE_TEST
        "Download the Google Test framework"
        OFF)
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2
        "Include this project's copy of the Catch2 test framework"
        OFF)
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST
        "Include this project's copy of the doctest test framework"
        OFF)
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_UT
        "Include this project's copy of the Boost.UT test framework"
        OFF)

# Control of what targets are built
option(APPROVAL_TESTS_BUILD_TESTING
        "Build self-tests. Note that these are always built if this is the top-level project"
        OFF)
option(APPROVAL_TESTS_BUILD_EXAMPLES
        "Build documentation examples. Note that these are always built if this is the top-level project"
        OFF)
