cmake_minimum_required(VERSION 3.8)
project(ApprovalTests_Catch2_Tests)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        main.cpp
        reporters/ReporterTests.cpp
        ApprovalExceptionTests.cpp
        StringWriterTests.cpp
        NamerTests.cpp
        FileApproverTests.cpp
        ApprovalsTests.cpp
        VectorTests.cpp
        CombinationTests.cpp
        StringUtilsTests.cpp
        SystemUtilsTests.cpp
        ToStringExample.cpp
        StyleGuide.h
        )
add_executable(${PROJECT_NAME} ${SOURCE_FILES} )
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
