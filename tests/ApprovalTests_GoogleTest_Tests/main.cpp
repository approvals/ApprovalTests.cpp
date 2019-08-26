// ReSharper disable once CppUnusedIncludeDirective
// begin-snippet: googletest_main
// main.cpp:
#define APPROVALS_GOOGLETEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
#include "Approvals.h"
// end-snippet

auto directory = ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
