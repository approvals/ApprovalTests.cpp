if (NOT APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION)
    return()
endif ()

project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
#        main.cpp
        BoostTestApprovalTestsTests.cpp
        )

# unit_test_framework

# Hints for specifying Boost location:
# 1. It's possible to specify your Boost location on the CMake command line,
# for example:
#  -DBOOST_ROOT=/Users/clare/Documents/develop/tools/boost/boost_1_71_0/
#  -DBOOST_ROOT=/usr/local/Cellar/boost/1.76.0/
# 2. In CLion, you can supply this argument in each of your CMake profiles, with:
#    Preferences -> Build, Execution, Deployment -> CMake -> 'CMake options:'
find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (Boost_FOUND)

    if (CYGWIN)
        # When ${Boost_INCLUDE_DIRS} is added as a SYSTEM location,
        # the cygwin builds fail to find <stdlib.h>.
        # So for just this platform, don't use SYSTEM.
        include_directories(${Boost_INCLUDE_DIRS})
    else ()
        include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
    endif ()
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (NOT "${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    include(WarningsAsErrors)
endif ()
