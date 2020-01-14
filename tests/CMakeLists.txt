add_subdirectory(Catch2_Tests)
add_subdirectory(GoogleTest_Tests)
add_subdirectory(DocTest_Tests)
add_subdirectory(UT_Tests)

if(APPROVAL_TESTS_ENABLE_CMAKE_INTEGRATION_TESTS)
    add_subdirectory(CMake_Tests)
endif()
