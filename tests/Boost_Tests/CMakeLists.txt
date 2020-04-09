project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        )

# Specific to Clare's Mac
#set(Boost_INCLUDE_DIR /Users/clare/Documents/develop/tools/boost/boost_1_71_0_install/include/ CACHE FILEPATH "" FORCE)

find_package(Boost 1.71.0 COMPONENTS unit_test_framework REQUIRED)
if (Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(WarningsAsErrors)
