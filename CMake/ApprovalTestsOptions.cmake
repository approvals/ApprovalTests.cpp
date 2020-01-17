option(APPROVAL_TESTS_ENABLE_CODE_COVERAGE "Enable coverage reporting for selected tests" OFF)

option(APPROVAL_TESTS_BUILD_CMAKE_INTEGRATION_TESTING "Enable tests that check our CMake integration" OFF)

option(APPROVAL_TESTS_BUILD_THIRD_PARTY
        "Include third_party directory. Note that these are always included if this is the top-level project"
        OFF)
option(APPROVAL_TESTS_BUILD_TESTING
        "Build self-tests. Note that these are always built if this is the top-level project"
        OFF)
option(APPROVAL_TESTS_BUILD_EXAMPLES
        "Build documentation examples. Note that these are always built if this is the top-level project"
        OFF)
