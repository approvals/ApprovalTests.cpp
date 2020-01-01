project(ut CXX)
set(CMAKE_CXX_STANDARD 17)
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Mimic the library names in BOOST.ut's own CMake files:
add_library(boost.ut ALIAS ut)
