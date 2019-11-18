project(GoogleTest_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
    main.cpp
    CompileAllIncludes.cpp
    GoogleTestApprovalsTests.cpp
    namers/GoogleNamerTest.cpp
    namers/GoogleFixtureNamerCustomizationTests.cpp
    )
target_link_libraries(${PROJECT_NAME} ApprovalTests gtest gtest_main)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(WarningsAsErrors)
