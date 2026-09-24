#define APPROVALS_DOCTEST_EXISTING_MAIN
#include <ApprovalTests.hpp>
#include "TestTracking.h"

TEST_CASE("Approval in module one")
{
    recordModuleTest(1);
    ApprovalTests::Approvals::verify("module one", ApprovalTests::Options().withReporter(
                                                      ApprovalTests::QuietReporter()));
}
