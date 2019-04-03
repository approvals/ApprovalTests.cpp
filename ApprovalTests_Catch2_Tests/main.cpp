//filesystem::
// ReSharper disable once CppUnusedIncludeDirective

// startcode catch_2_main
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// endcode

// startcode use_subdirectory_in_main
auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
// endcode
