project(ApprovalTests CXX)
set(CMAKE_CXX_STANDARD 11)
add_library(${PROJECT_NAME} INTERFACE)
add_library(ApprovalTests::ApprovalTests ALIAS ApprovalTests)
target_include_directories(${PROJECT_NAME}
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )
target_compile_options(${PROJECT_NAME} INTERFACE $<$<CXX_COMPILER_ID:MSVC>:/FC>)

if (("${CMAKE_GENERATOR}" MATCHES "Ninja") AND (${CMAKE_UNITY_BUILD}))
    # In case this is a Ninja Unity in-source build, disabling the
    # compile-time checking of __FILE__, to fix the compilation of our
    # Catch2 tests, and others which depend on __FILE__ - which then go on to pass,
    # even when built inside source trees.
    message(NOTICE "Ninja with Unity build detected: disabling unnecessary ApprovalTests compile-time check of __FILE__")
    target_compile_definitions(${PROJECT_NAME} INTERFACE APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK)
endif ()
