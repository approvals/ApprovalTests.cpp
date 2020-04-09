project(Boost_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        main.cpp
        )


# https://github.com/G-PublicChain/G/blob/430fc851ee73b71c1c84f54cac1a9d7d8d74ed73/Builds/CMake/deps/Boost.cmake

# https://github.com/almsilva/cpp_basic_starter/blob/master/CMakeLists.txt


# Specific to Clare's Mac
set(Boost_INCLUDE_DIR /Users/clare/Documents/develop/tools/boost/boost_1_71_0_install/include/ CACHE FILEPATH "" FORCE)

find_package(Boost 1.71.0 COMPONENTS unit_test_framework REQUIRED)
if (Boost_FOUND)
    #    list(REMOVE_ITEM sources "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

    include_directories(${Boost_INCLUDE_DIRS})
    #    file(GLOB TEST_SOURCES "test/*.cpp")

    #    foreach(testFile ${TEST_SOURCES})
    #        get_filename_component(testFileName ${testFile} NAME_WE)
    #        add_executable(${testFileName}_test ${testFile} ${sources})
    #        target_link_libraries(${testFileName}_test ${Boost_LIBRARIES})
    #        add_test(NAME ${testFileName}_test
    #                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build
    #                COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build/${testFileName}_test)
    #    endforeach(testFile)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

endif ()


#find_package(Boost COMPONENTS test REQUIRED)
target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests)

#target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${Boost_INCLUDE_DIR})
#target_link_libraries(${PROJECT_NAME} PUBLIC Boost::test)

include(WarningsAsErrors)
