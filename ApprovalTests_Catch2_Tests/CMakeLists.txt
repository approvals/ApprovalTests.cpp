project(ApprovalTests_Catch2_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
        main.cpp
        ApprovalExceptionTests.cpp
        ApprovalsTests.cpp
        ApprovalTests.hpp
        CombinationTests.cpp
        FileApproverTests.cpp
        NamerTests.cpp
        PairUtilities.h
        StringUtilsTests.cpp
        StringWriterTests.cpp
        StyleGuide.h
        SystemUtilsTests.cpp
        ToStringExample.cpp
        ToStringTemplateExample.cpp
        ToStringWrapperExample.cpp
        VectorTests.cpp
        reporters/ReporterTests.cpp
        reporters/DoNothingLauncher.h
        reporters/FakeReporter.h
        reporters/TestReporter.h
        reporters/ReporterTests.cpp
        utilities/MachineBlockerTests.cpp
        reporters/BlockingReporterTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    target_compile_options(${PROJECT_NAME} PRIVATE
#        /W4
#        /WX
#        /wd4100 # unreferenced formal parameter
#        /wd4244 # conversion from 'int' to 'char', possible loss of data
#        /wd2220 # warning treated as error - no 'object' file generated
#        )
endif()
