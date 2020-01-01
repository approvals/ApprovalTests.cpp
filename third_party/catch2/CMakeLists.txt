project(catch2 CXX)
set(CMAKE_CXX_STANDARD 11)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Mimic the library names in Catch2's own CMake files:
add_library(Catch2 ALIAS catch2)
add_library(Catch2::Catch2 ALIAS catch2)
