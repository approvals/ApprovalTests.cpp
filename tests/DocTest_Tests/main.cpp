// begin-snippet: doctest_main
// main.cpp:
#define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

#include <memory>
#include "ApprovalTests/reporters/EnvironmentVariableReporter.h"

using namespace ApprovalTests;

auto directoryDisposer = Approvals::useApprovalsSubdirectory("approval_tests");

auto defaultReporterDisposer =
    Approvals::useAsDefaultReporter(std::make_shared<EnvironmentVariableReporter>());
