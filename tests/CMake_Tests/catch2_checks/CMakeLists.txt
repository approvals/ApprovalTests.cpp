if (NOT APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION)
    return()
endif ()

set(CMAKE_CXX_STANDARD 11)

# Create one library for each of the Catch2 targets and aliases we require to exist

# This is the one users are recommended to use:
add_library(
        Catch2Catch2 catch2_cmake_checks.cpp)
target_link_libraries(
        Catch2Catch2 Catch2v2::Catch2v2)

add_library(
        capital_Catch2 catch2_cmake_checks.cpp)
target_link_libraries(
        capital_Catch2 Catch2v2)

if (NOT_SUBPROJECT)
    # Don't build this if we are in a sub-project, in case the user has pulled in
    # a full Catch2 clone, as in that case, our old, non-standard library won't exist...
    #
    # This one is historical, left over from when ApprovalTests.cpp was first created.
    # We could encourage users to move away from it.
    add_library(
            lower_case_catch2 catch2_cmake_checks.cpp)
    target_link_libraries(
            lower_case_catch2 catch2v2)
endif ()

# Check that our real target name for Catch2 matches that used in the Catch2 project
target_compile_definitions(Catch2v2 INTERFACE DUMMY_TEST_DEFINE)
