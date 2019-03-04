cmake_minimum_required(VERSION 3.8)
project(ApprovalTests_GoogleTest_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        GoogleTestApprovalsTests.cpp
        GoogleNamerTest.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests gtest gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
