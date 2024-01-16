//filesystem::
// ReSharper disable once CppUnusedIncludeDirective

#define TEST_COMMIT_REVERT_CATCH

// begin-snippet: catch_2_main
// main.cpp:
#define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

// begin-snippet: use_subdirectory_in_main
auto directoryDisposer =
    ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
// end-snippet

// begin-snippet: use_as_default_reporter_in_main
// main.cpp:
#include <memory>
auto defaultReporterDisposer = ApprovalTests::Approvals::useAsDefaultReporter(
    std::make_shared<ApprovalTests::DiffReporter>());
// end-snippet
