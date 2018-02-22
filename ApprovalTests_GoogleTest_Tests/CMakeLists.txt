cmake_minimum_required(VERSION 3.8)
project(ApprovalTests_GoogleTest_Tests)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
        main.cpp
        GoogleTestApprovalsTests.cpp
		GoogleNamerTest.cpp
        )

if(MSVC)
    # Suppress compiler warnings, until I can access a newer Google Test build
    #   C:\Users\Clare\Documents\Programming\tools\gtest\gtest-1.6.0-vs2015-update2\include\gtest/gtest-printers.h(497): warning C4996: 'std::tr1': warning STL4002: The non-Standard std::tr1 namespace and TR1-only machinery are deprecated and will be REMOVED. You can define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING to acknowledge that you have received this warning.
    #   C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\14.12.25827\include\tuple(1137): note: see declaration of 'std::tr1'
    add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES} )

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} GTest::GTest GTest::Main)
