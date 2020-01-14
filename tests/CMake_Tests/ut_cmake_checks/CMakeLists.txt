if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.2) OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0))
    set(CMAKE_CXX_STANDARD 20)

    # This is the one users are recommended to use:
    add_executable(
            ut_cmake_checks_boost_ut ut_cmake_checks.cpp)
    target_link_libraries(
            ut_cmake_checks_boost_ut boost.ut)

    # This one is historical, left over from when ApprovalTests.cpp was first created.
    # We could encourage users to move away from it.
    add_executable(
            ut_cmake_checks_ut ut_cmake_checks.cpp)
    target_link_libraries(
            ut_cmake_checks_ut ut)

    # Check that our real target name for Boost.UT matches that used in the Catch2 project
    target_compile_definitions(boost.ut INTERFACE DUMMY_TEST_DEFINE)
else()
    MESSAGE("The [Boost].UT integration with Approval Tests requires source_location support by the compiler, therefore it's disabled")
endif()
