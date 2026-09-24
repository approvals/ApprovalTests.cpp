#define APPROVALS_DOCTEST_EXTERNAL_MAIN
#include <ApprovalTests.hpp>
#include "TestTracking.h"

TEST_CASE("Another approval in module one")
{
    recordModuleTest(4);
    ApprovalTests::Approvals::verify(
        "another module one test",
        ApprovalTests::Options().withReporter(ApprovalTests::QuietReporter()));
}
