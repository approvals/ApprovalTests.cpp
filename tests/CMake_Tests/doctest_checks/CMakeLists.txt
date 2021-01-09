if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

set(CMAKE_CXX_STANDARD 11)

# This is the one users are recommended to use:
add_library(
        doctest_doctest doctest_cmake_checks.cpp)
target_link_libraries(
        doctest_doctest doctest::doctest)

add_library(
        capital_doctest doctest_cmake_checks.cpp)
target_link_libraries(
        capital_doctest doctest)

# Check that our real target name for doctest matches that used in the doctest project
target_compile_definitions(doctest INTERFACE DUMMY_TEST_DEFINE)
