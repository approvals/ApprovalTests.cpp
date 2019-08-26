// begin-snippet: doctest_main
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
#include "Approvals.h"
// end-snippet

auto directory = ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
