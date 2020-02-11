project(DocTest_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
    main.cpp
    namers/DocTestNamerTests.cpp
    docs/DocTestDocsSamples.cpp
    namers/NamerTests.cpp
    docs/DisposableSamples.cpp
    docs/ForgottenToConfigure.cpp
    utilities/ExceptionCollectorTests.cpp
    utilities/FileUtilsTests.cpp
    DocTestApprovalTestTests.cpp
    reporters/CustomReporterTests.cpp
    reporters/CommandLineReporterTests.cpp
    )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests doctest::doctest)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if(APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME ${PROJECT_NAME}_coverage
            EXECUTABLE ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME})
endif()

include(WarningsAsErrors)
