# -------------------------------------------------------------------
# Control what targets are built.
# Note that these are always built if this is the top-level project.
option(APPROVAL_TESTS_BUILD_TESTING
        "Build self-tests."
        ${NOT_SUBPROJECT})
option(APPROVAL_TESTS_BUILD_EXAMPLES
        "Build documentation examples."
        ${NOT_SUBPROJECT})
option(APPROVAL_TESTS_BUILD_DOCS
        "Build documentation - if Doxygen and Sphinx are found."
        ${NOT_SUBPROJECT})

# -------------------------------------------------------------------
# Control which of our copies of header-only third_party libraries are made available.
# These only affect builds where ApprovalTests.cpp is a sub-project.
# All the third-party libraries are made available
# if this is the top-level project, so that we can run our tests.
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2
        "Include this project's copy of the Catch2 test framework"
        ${NOT_SUBPROJECT})
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST
        "Include this project's copy of the doctest test framework"
        ${NOT_SUBPROJECT})
option(APPROVAL_TESTS_BUILD_THIRD_PARTY_UT
        "Include this project's copy of the Boost.UT test framework"
        ${NOT_SUBPROJECT})

# -------------------------------------------------------------------
# Options to control the behaviour of our builds.
option(APPROVAL_TESTS_ENABLE_CODE_COVERAGE
        "Enable coverage reporting for selected tests"
        OFF)
