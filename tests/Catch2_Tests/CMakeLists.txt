project(Catch2_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
    main.cpp
    core/ApprovalExceptionTests.cpp
    ApprovalsTests.cpp
    ApprovalTests.hpp
    CombinationTests.cpp
    core/FileApproverTests.cpp
    PairUtilities.h
    StyleGuide.h
    VectorTests.cpp
    documentation/Catch2DocumentationSamples.cpp
    documentation/OverviewExamples.cpp
    documentation/ToStringExample.cpp
    documentation/ToStringTemplateExample.cpp
    documentation/ToStringWrapperExample.cpp
    documentation/Tutorial.cpp
    namers/NamerTests.cpp
    reporters/BlockingReporterTests.cpp
    reporters/DoNothingLauncher.h
    reporters/FakeReporter.h
    reporters/ReporterTests.cpp
    reporters/ReporterTests.cpp
    reporters/TestReporter.h
    utilities/FileUtilsSystemSpecificTests.cpp
    utilities/MachineBlockerTests.cpp
    utilities/StringUtilsTests.cpp
    utilities/SystemUtilsTests.cpp
    writers/StringWriterTests.cpp
    )
target_link_libraries(${PROJECT_NAME} ApprovalTests catch2)
target_compile_definitions(${PROJECT_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /WX
        )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    string(REGEX REPLACE " /W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /WX
        )
endif()
