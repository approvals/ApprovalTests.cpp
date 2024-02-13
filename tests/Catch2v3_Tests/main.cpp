//filesystem::
// ReSharper disable once CppUnusedIncludeDirective

// begin-snippet: catch_2_v3_main
// main.cpp:
#define APPROVALS_CATCH2_V3 // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");

#include <memory>
auto defaultReporterDisposer = ApprovalTests::Approvals::useAsDefaultReporter(
    std::make_shared<ApprovalTests::DiffReporter>());
