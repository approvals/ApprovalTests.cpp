#define APPROVALS_DOCTEST_EXTERNAL_MAIN
#define APPROVALS_DOCTEST_EXTERNAL_MAIN_IMPLEMENTATION
#include <ApprovalTests.hpp>
#include "TestTracking.h"

TEST_CASE("Approval in module one")
{
    recordModuleTest(1);
    ApprovalTests::Approvals::verify("module one", ApprovalTests::Options().withReporter(
                                                      ApprovalTests::QuietReporter()));
}
