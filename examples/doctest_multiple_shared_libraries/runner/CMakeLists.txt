add_executable(${variant}_runner main.cpp)
set_target_properties(${variant}_runner PROPERTIES ENABLE_EXPORTS ON)
configure_doctest_target(${variant}_runner ${APPROVALS_PROVIDER})
target_link_libraries(${variant}_runner PRIVATE ${CMAKE_DL_LIBS})
