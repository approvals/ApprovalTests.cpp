cmake_minimum_required(VERSION 3.8)
project(ApprovalTests.cpp)
set(CMAKE_CXX_STANDARD 17)
include_directories(lib)
enable_testing()

add_subdirectory(ApprovalTests)
add_subdirectory(ApprovalTests_Catch1_Tests)
add_subdirectory(ApprovalTests_Catch2_Tests)

add_subdirectory(lib/googletest-release-1.8.1)

# We need at least Google Test 1.8, as that is the first version where
# TestInfo provides the path to the source file of tests being run
set(GTEST_ROOT "D:/Users/Clare/Documents/Programming/github/ApprovalTests.cpp/lib/googletest-release-1.8.1")
set(GTEST_INCLUDE_DIR "D:/Users/Clare/Documents/Programming/github/ApprovalTests.cpp/lib/googletest-release-1.8.1/googletest/include")
set(GTEST_LIBRARY "D:/Users/Clare/Documents/Programming/github/ApprovalTests.cpp/cmake-build-debug/lib/googletest-release-1.8.1/googlemock/gtest/libgtestd.a")
set(GTEST_MAIN_LIBRARY "D:/Users/Clare/Documents/Programming/github/ApprovalTests.cpp/cmake-build-debug/lib/googletest-release-1.8.1/googlemock/gtest/libgtest_maind.a")
set(GTEST_ROOT "cmake-build-debug/lib/googletest-release-1.8.1")
find_package(GTest 1.8)
if(GTEST_FOUND)
    message("Google Test found in ${GTEST_INCLUDE_DIRS}")
    add_subdirectory(ApprovalTests_GoogleTest_Tests)
else()
    message("Google Test not found")
endif()
