// begin-snippet: doctest_main
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

using namespace ApprovalTests;

auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
