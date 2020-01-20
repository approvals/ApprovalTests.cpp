# -------------------------------------------------------------------
# Control what targets are built.
# Note that these are always built if this is the top-level project.
option(APPROVAL_TESTS_BUILD_TESTING
        "Build self-tests."
        OFF)
option(APPROVAL_TESTS_BUILD_EXAMPLES
        "Build documentation examples."
        OFF)

# -------------------------------------------------------------------
# Control which of our copies of header-only third_party libraries are made available.
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2
        "Include this project's copy of the Catch2 test framework"
        OFF)
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST
        "Include this project's copy of the doctest test framework"
        OFF)
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_UT
        "Include this project's copy of the Boost.UT test framework"
        OFF)

# -------------------------------------------------------------------
# Options to control the behaviour of our builds.
option(APPROVAL_TESTS_ENABLE_CODE_COVERAGE
        "Enable coverage reporting for selected tests"
        OFF)
