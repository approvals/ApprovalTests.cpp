project(ApprovalTests_Catch1_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
    main.cpp
    ApprovalsTests.cpp)
target_link_libraries(${PROJECT_NAME} ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
