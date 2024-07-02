if (NOT APPROVAL_TESTS_ENABLE_CATCH2_INTEGRATION)
    return()
endif ()

if (NOT TARGET Catch2v2_Amalgamated)
    project(Catch2v2_Amalgamated CXX)
    set(CMAKE_CXX_STANDARD 17)
    add_library(${PROJECT_NAME} catch_amalgamated.cpp)
    target_include_directories(${PROJECT_NAME}
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

    add_library(Catch2v2_Amalgamated::Catch2v2_Amalgamated ALIAS Catch2v2_Amalgamated)

endif ()
