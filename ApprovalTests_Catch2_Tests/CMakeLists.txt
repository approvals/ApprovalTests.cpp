project(ApprovalTests_Catch2_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
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
        ToStringTemplateExample.cpp
        ToStringWrapperExample.cpp
        StyleGuide.h
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
