if (NOT APPROVAL_TESTS_ENABLE_BOOST_TEST_INTEGRATION)
    return()
endif ()

# begin-snippet: boost_starter_cmake
set(EXE_NAME boost_starter)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.60.0 COMPONENTS REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Cannot find Boost libraries")
endif ()

include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(${EXE_NAME}
        boost_starter_main.cpp
        boost_starter_test.cpp
        )
target_link_libraries(${EXE_NAME} ApprovalTests::ApprovalTests ${Boost_LIBRARIES})

add_test(NAME ${EXE_NAME} COMMAND ${EXE_NAME})
# end-snippet
