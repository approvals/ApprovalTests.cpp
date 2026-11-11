add_executable(${variant}_runner main.cpp)
set_target_properties(${variant}_runner PROPERTIES ENABLE_EXPORTS ON)
configure_doctest_target(${variant}_runner ${APPROVALS_PROVIDER})
target_link_libraries(${variant}_runner PRIVATE ${CMAKE_DL_LIBS})
if (CYGWIN)
    # Cygwin exports every symbol from the runner. Keep the static Approval Tests
    # library out of the exports, as on Windows, or each module gets two copies.
    target_link_options(${variant}_runner PRIVATE -Wl,--exclude-libs,ALL)
endif ()
