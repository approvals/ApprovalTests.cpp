project(ApprovalTests_DocTest_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
        main.cpp
        DocTestNamerTests.cpp
        namers/NamerTests.cpp)
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
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
        /WX
        )
endif()
