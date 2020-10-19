if (NOT APPROVAL_TESTS_ENABLE_DOCTEST_INTEGRATION)
    return()
endif ()

project(fmt_approvals_demo)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        FmtTests.cpp
        FmtAsDefaultTests.cpp
        )
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests doctest::doctest)
# begin-snippet: fmt_cmake
target_link_libraries(${PROJECT_NAME} fmt::fmt)
# end-snippet

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

#include(WarningsAsErrors)
