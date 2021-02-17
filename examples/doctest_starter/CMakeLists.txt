if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

# begin-snippet: doctest_starter_cmake
set(EXE_NAME doctest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        doctest_starter_main.cpp
        doctest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests doctest::doctest)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
