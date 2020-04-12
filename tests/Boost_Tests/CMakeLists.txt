project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        )

# unit_test_framework
find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

#include(WarningsAsErrors)
