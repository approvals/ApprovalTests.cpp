find_program(mdsnippets_FOUND mdsnippets)
if (NOT mdsnippets_FOUND)
    message(STATUS "mdsnippets not found: Will not regenerate markdown files")
    return()
endif ()

add_custom_command(OUTPUT ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD}
        COMMAND mdsnippets
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

# Nice named target so we can run the job easily
add_custom_target(RunMdsnippets DEPENDS ${DOCS_FAKE_OUTPUT_FILE_TO_FORCE_BUILD})
