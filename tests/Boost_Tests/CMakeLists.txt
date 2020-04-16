project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        BoostTestApprovalTestsTests.cpp
        )

# unit_test_framework

# Hints for specifying Boost location:
# 1. It's possible to specify your Boost location on the CMake command line,
# for example:
#  -DBOOST_ROOT=/Users/clare/Documents/develop/tools/boost/boost_1_71_0/
# 2. In CLion, you can supply this argument in each of your CMake profiles, with:
#    Preferences -> Build, Execution, Deployment -> CMake -> 'CMake options:'
find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (Boost_FOUND)

    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

message("CMAKE_SYSTEM_NAME = ${CMAKE_SYSTEM_NAME}")
if (NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    message("Treating warnings as errors in Boost_Tests")
    include(WarningsAsErrors)
else ()
    message("NOT Treating warnings as errors in Boost_Tests")
endif ()
