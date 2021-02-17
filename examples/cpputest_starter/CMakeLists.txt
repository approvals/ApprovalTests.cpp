if (NOT APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION)
    return()
endif ()

# begin-snippet: cpputest_starter_cmake
set(EXE_NAME cpputest_starter)
set(CMAKE_CXX_STANDARD 11)
add_executable(${EXE_NAME}
        cpputest_starter_main.cpp
        cpputest_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests CppUTest)

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
