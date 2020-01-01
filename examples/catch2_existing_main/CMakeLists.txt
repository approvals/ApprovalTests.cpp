project(catch2_existing_main)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        Catch2ApprovalsTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests Catch2::Catch2)
target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/Catch2_Tests)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
