add_subdirectory(Catch2_Tests)
add_subdirectory(GoogleTest_Tests)
add_subdirectory(DocTest_Tests)
add_subdirectory(UT_Tests)

if(NOT_SUBPROJECT OR APPROVAL_TESTS_BUILD_CMAKE_INTEGRATION_TESTING)
    add_subdirectory(CMake_Tests)
endif()
