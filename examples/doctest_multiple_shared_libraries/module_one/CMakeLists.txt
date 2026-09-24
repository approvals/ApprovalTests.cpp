# Two source files, so this module checks several doctest sources in one library.
add_test_module(${variant}_module_one ${variant}_runner ${APPROVALS_PROVIDER}
        ModuleOne.cpp ModuleOneExtra.cpp)
# Keep implementation and declaration-only includes in separate translation units.
set_target_properties(${variant}_module_one PROPERTIES UNITY_BUILD OFF)
