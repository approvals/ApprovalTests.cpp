if (NOT APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION)
    return()
endif ()

project(cpputest_existing_main)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        CppUTestApprovalsTestsExistingMain.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests CppUTest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
