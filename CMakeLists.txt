cmake_minimum_required(VERSION 3.8)
project(ApprovalTests.cpp)
set(CMAKE_CXX_STANDARD 17)
include_directories(lib)
enable_testing()

add_subdirectory(ApprovalTests)
add_subdirectory(ApprovalTests_Catch1_Tests)
add_subdirectory(ApprovalTests_Catch2_Tests)


# We need at least Google Test 1.8, as that is the first version where
# TestInfo provides the path to the source file of tests being run
#set(GTEST_ROOT "C:/Users/Clare/Documents/Programming/tools/gtest/gtest-1.8.0")
#set(GTEST_INCLUDE_DIR "C:/Users/Clare/Documents/Programming/tools/gtest/gtest-1.8.0/include")
#set(GTEST_LIBRARY "C:/Users/Clare/Documents/Programming/tools/gtest/gtest-1.8.0/msvc/gtest/Debug/gtest.lib")
#set(GTEST_MAIN_LIBRARY "C:/Users/Clare/Documents/Programming/tools/gtest/gtest-1.8.0/msvc/gtest/Debug/gtest_main.lib")
find_package(GTest 1.8)
if(GTEST_FOUND)
    message("Google Test found in ${GTEST_INCLUDE_DIRS}")
    add_subdirectory(ApprovalTests_GoogleTest_Tests)
else()
    message("Google Test not found")
endif()
