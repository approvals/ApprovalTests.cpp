if (NOT APPROVAL_TESTS_ENABLE_GOOGLETEST_INTEGRATION)
    return()
endif ()

project(googletest_existing_main)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        GoogleTestApprovalsTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests gtest gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
