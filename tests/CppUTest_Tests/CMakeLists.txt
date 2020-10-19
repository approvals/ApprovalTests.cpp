if (NOT APPROVAL_TESTS_ENABLE_CPPUTEST_INTEGRATION)
    return()
endif ()

project(CppUTest_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
        main.cpp
        CppUTestApprovalsTests.cpp
        namers/CppUTestNamerTests.cpp
        )

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests CppUTest)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME ${PROJECT_NAME}_coverage
            EXECUTABLE ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME})
endif ()

#include(WarningsAsErrors)
