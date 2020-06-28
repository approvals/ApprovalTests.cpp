find_program(mdsnippets_FOUND mdsnippets)
if (NOT mdsnippets_FOUND)
    message(STATUS "mdsnippets not found: Will not regenerate markdown files")
    return()
endif ()

file(GLOB_RECURSE
        APPROVAL_TESTS_ALL_TEST_FILES
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/tests/*.approved.*
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
        ${PROJECT_SOURCE_DIR}/tests/*.h
        )

file(GLOB_RECURSE
        APPROVAL_TESTS_ALL_EXAMPLE_FILES
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/examples/*.approved.*
        ${PROJECT_SOURCE_DIR}/examples/*.cpp
        ${PROJECT_SOURCE_DIR}/examples/*.h
        )

file(GLOB
        APPROVAL_TESTS_ALL_ROOT_SOURCE_MD_FILES
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/mdsource/*.source.md)

file(GLOB_RECURSE
        APPROVAL_TESTS_ALL_DOC_INCLUDE_MD_FILES
        CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/doc/*.include.md)

# If any .source.md files have been changed, or their inputs,
# rerun mdsnippets
list(GET APPROVAL_TESTS_GEN_DOC_MD_FILES 0 FIRST_GENERATED_MD_FILE)
set(OTHER_GENERATED_MD_FILES ${APPROVAL_TESTS_GEN_DOC_MD_FILES})
list(REMOVE_AT OTHER_GENERATED_MD_FILES 0)

add_custom_command(OUTPUT ${FIRST_GENERATED_MD_FILE}
        COMMAND mdsnippets
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS
        ${APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES}
        ${APPROVAL_TESTS_ALL_DOC_INCLUDE_MD_FILES}
        ${APPROVAL_TESTS_ALL_ROOT_SOURCE_MD_FILES}
        ${APPROVAL_TESTS_PUBLIC_SOURCE}
        ${APPROVAL_TESTS_ALL_TEST_FILES}
        ${APPROVAL_TESTS_ALL_EXAMPLE_FILES}
        ${PROJECT_SOURCE_DIR}/mdsnippets.json
        BYPRODUCTS ${OTHER_GENERATED_MD_FILES}
        )

# Nice named target so we can run the job easily
add_custom_target(RunMdsnippets DEPENDS ${FIRST_GENERATED_MD_FILE})
