project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        )

# Specific to Clare's Mac - temporary for testing...
if (DEFINED ENV{USER})
    if ("$ENV{USER}" STREQUAL "clare")
        set(BOOST_ROOT /Users/clare/Documents/develop/tools/boost/boost_1_71_0/
                CACHE FILEPATH "" FORCE)
    endif ()
endif ()

# unit_test_framework
find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (Boost_FOUND)

    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

#include(WarningsAsErrors)
