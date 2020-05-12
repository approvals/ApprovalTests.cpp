find_program(mdsnippets_FOUND mdsnippets)
if (NOT mdsnippets_FOUND)
    message(STATUS "mdsnippets not found: Will not regenerate markdown files")
    return()
endif ()

# If any .source.md files have been changed, rerun mdsnippets
# TODO Also add dependency on files containing any snippets
list(GET APPROVAL_TESTS_GEN_DOC_MD_FILES 0 FIRST_GENERATED_MD_FILE)
add_custom_command(OUTPUT ${FIRST_GENERATED_MD_FILE}
        COMMAND mdsnippets
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        DEPENDS ${APPROVAL_TESTS_ALL_DOC_SOURCE_MD_FILES}
        BYPRODUCTS ${APPROVAL_TESTS_GEN_DOC_MD_FILES}
        )

# Nice named target so we can run the job easily
add_custom_target(RunMdsnippets DEPENDS ${FIRST_GENERATED_MD_FILE})
