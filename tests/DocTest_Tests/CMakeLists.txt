project(DocTest_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
        main.cpp
        ApprovalsTests.cpp
        CombinationTests.cpp
        CustomizingToStringTests.cpp
        DocTestApprovalTestTests.cpp
        VectorTests.cpp
        comparators/ComparatorDisposerTest.cpp
        core/ApprovalExceptionTests.cpp
        core/FileApproverTests.cpp
        core/OptionsTests.cpp
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
        scrubbers/ScrubberTests.cpp
        utilities/CartesianProductTests.cpp
        utilities/ExceptionCollectorTests.cpp
        utilities/FileUtilsSystemSpecificTests.cpp
        utilities/FileUtilsTests.cpp
        utilities/StringUtilsTests.cpp
        utilities/SystemUtilsTests.cpp
        writers/StringWriterTests.cpp
        )
target_link_libraries(${PROJECT_NAME}
        ApprovalTests::ApprovalTests
        doctest::doctest)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
# begin-snippet: show_deprecation_warnings_cmake
# Replace ${PROJECT_NAME} with the name of your test executable:
target_compile_definitions(${PROJECT_NAME} PRIVATE -DAPPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS=1)
# end-snippet

# begin-snippet: hide_deprecated_code_cmake
# Replace ${PROJECT_NAME} with the name of your test executable:
target_compile_definitions(${PROJECT_NAME} PRIVATE -DAPPROVAL_TESTS_HIDE_DEPRECATED_CODE=1)
# end-snippet

if (APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME ${PROJECT_NAME}_coverage
            EXECUTABLE ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME})
endif ()

if (UNIX)
    # Temporarily don't treat warnings as errors on Windows until I can find a reliable
    # way to fix this and a whole host of other C4996 messages for various date-and-time functions
    # on Windows with the VC compiler and with clang-cl:
    #
    # C:\Code\ApprovalTests.cpp\tests\DocTest_Tests\scrubbers\ScrubberTests.cpp(90,57):
    # error C2220: the following warning is treated as an error
    #
    # C:\Code\ApprovalTests.cpp\tests\DocTest_Tests\scrubbers\ScrubberTests.cpp(90,57):
    # warning C4996: 'localtime': This function or variable may be unsafe. Consider using localtime_s instead.
    #
    # To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

    include(WarningsAsErrors)
endif (UNIX)