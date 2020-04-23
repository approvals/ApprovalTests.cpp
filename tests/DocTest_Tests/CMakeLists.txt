project(DocTest_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
        main.cpp
        ApprovalsTests.cpp
        CombinationTests.cpp
        DocTestApprovalTestTests.cpp
        VectorTests.cpp
        comparators/ComparatorDisposerTest.cpp
        core/ApprovalExceptionTests.cpp
        core/FileApproverTests.cpp
        docs/CombinationsSampleCode.cpp
        docs/DisposableSamples.cpp
        docs/DocTestDocsSamples.cpp
        docs/ForgottenToConfigure.cpp
        docs/OverviewExamples.cpp
        docs/ToStringExample.cpp
        docs/ToStringTemplateExample.cpp
        docs/ToStringWrapperExample.cpp
        docs/Tutorial.cpp
        namers/DocTestNamerTests.cpp
        namers/NamerTests.cpp
        reporters/BlockingReporterTests.cpp
        reporters/CIBuildOnlyReporterTests.cpp
        reporters/CommandLineReporterTests.cpp
        reporters/CustomReporterTests.cpp
        reporters/DoNothingLauncher.h
        reporters/FakeReporter.h
        reporters/ReporterTests.cpp
        reporters/ReporterTests.cpp
        reporters/TestReporter.h
        scrubbers/GuidScrubberTests.cpp
        utilities/CartesianProductTests.cpp
        utilities/ExceptionCollectorTests.cpp
        utilities/FileUtilsSystemSpecificTests.cpp
        utilities/FileUtilsTests.cpp
        utilities/StringUtilsTests.cpp
        utilities/SystemUtilsTests.cpp
        writers/StringWriterTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests doctest::doctest)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
# begin-snippet: show_deprecation_warnings_cmake
# Replace ${PROJECT_NAME} with the name of your test executable:
target_compile_definitions(${PROJECT_NAME} PRIVATE APPROVALTESTS_SHOW_DEPRECATION_WARNINGS)
# end-snippet

if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME ${PROJECT_NAME}_coverage
            EXECUTABLE ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME})
endif ()

include(WarningsAsErrors)
