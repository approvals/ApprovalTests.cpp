project(Catch2_Tests)
set(CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME}
    main.cpp
    PairUtilities.h
    StyleGuide.h
    comparators/ComparatorDisposerTest.cpp
    core/FileApproverTests.cpp
    docs/Catch2DocsSamples.cpp
    namers/NamerTests.cpp
    utilities/CartesianProductTests.cpp
    utilities/FileUtilsSystemSpecificTests.cpp
    utilities/MachineBlockerTests.cpp
    )

set_source_files_properties(main.cpp PROPERTIES SKIP_UNITY_BUILD_INCLUSION YES)

target_link_libraries(${PROJECT_NAME} ApprovalTests::ApprovalTests Catch2::Catch2)
target_compile_definitions(${PROJECT_NAME} PRIVATE CATCH_CONFIG_FAST_COMPILE)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if(APPROVAL_TESTS_ENABLE_CODE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME ${PROJECT_NAME}_coverage
            EXECUTABLE ${PROJECT_NAME}
            DEPENDENCIES ${PROJECT_NAME})
endif()

include(WarningsAsErrors)
