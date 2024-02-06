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
        "Include this project's copy of the Catch2v2 test framework"
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

# -------------------------------------------------------------------
# Advanced options - which are not documented.
# These interact in complication ways with the existing CMake options,
# and documenting these interactions would clutter the docs
# considerably.
option(APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION
        "Enable the Boost.Test integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION)

option(APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION
        "Enable the Catch2 integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION)

option(APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION
        "Enable the Catch2v3 integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_CATCH2V3_INTEGRATION)

option(APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION
        "Enable the CppUTest integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION)
if (CYGWIN)
    MESSAGE(WARNING "The CppUTest integration with Approval Tests does not build on this platform, CygWin, therefore it's disabled")
    set(APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION OFF CACHE BOOL "" FORCE)
endif()

option(APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION
        "Enable the doctest integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)

option(APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION
        "Enable the GoogleTest integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION)

option(APPROVAL_TESTS_ENABLE_UT_INTEGRATION
        "Enable the Boost.UT integration and testing"
        ON)
mark_as_advanced(APPROVAL_TESTS_ENABLE_UT_INTEGRATION)
