if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.2) OR (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION GREATER_EQUAL 9.0))
    set(CMAKE_CXX_STANDARD 20)

    # This is the one users are recommended to use:
    add_executable(
            ut_cmake_checks_boost_ut ut_cmake_checks.cpp)
    target_link_libraries(
            ut_cmake_checks_boost_ut boost.ut)
    add_test(
            NAME
            ut_cmake_checks_boost_ut
            COMMAND
            ut_cmake_checks_boost_ut
    )

    if(NOT_SUBPROJECT)
        # Don't build this if we are in a sub-project, in case the user has pulled in
        # a full Boost.ut clone, as in that case, our old, non-standard library won't exist...
        #
        # This one is historical, left over from when ApprovalTests.cpp was first created.
        # We could encourage users to move away from it.
        add_executable(
                ut_cmake_checks_ut ut_cmake_checks.cpp)
        target_link_libraries(
                ut_cmake_checks_ut Boost.ut)
        add_test(
                NAME
                ut_cmake_checks_ut
                COMMAND
                ut_cmake_checks_ut
        )
    endif()

    # Check that our real target name for Boost.UT matches that used in the Catch2 project
    target_compile_definitions(boost.ut INTERFACE DUMMY_TEST_DEFINE)
else()
    MESSAGE("The [Boost].UT integration with Approval Tests requires source_location support by the compiler, therefore it's disabled")
endif()
