set(CMAKE_CXX_STANDARD 11)

# Create one executable for each of the Catch2 targets and aliases we require to exist

# This is the one users are recommended to use:
add_executable(
        catch2_cmake_checks_Catch2Catch2 catch2_cmake_checks.cpp)
target_link_libraries(
        catch2_cmake_checks_Catch2Catch2 Catch2::Catch2)

add_executable(
        catch2_cmake_checks_capital_Catch2 catch2_cmake_checks.cpp)
target_link_libraries(
        catch2_cmake_checks_capital_Catch2 Catch2)

# This one is historical, left over from when ApprovalTests.cpp was first created.
# We could encourage users to move away from it.
add_executable(
        catch2_cmake_checks_lower_case_catch2 catch2_cmake_checks.cpp)
target_link_libraries(
        catch2_cmake_checks_lower_case_catch2 catch2)
