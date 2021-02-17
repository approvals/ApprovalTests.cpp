if (NOT APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION)
    return()
endif ()

# begin-snippet: googletest_starter_cmake
set(EXE_NAME googletest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        googletest_starter_main.cpp
        googletest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests gtest gtest_main)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
