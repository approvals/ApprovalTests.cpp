#define APPROVALS_DOCTEST_LISTENER_NAME "TestModuleTwo"
#define APPROVALS_DOCTEST_EXTERNAL_MAIN
#define APPROVALS_DOCTEST_EXTERNAL_MAIN_IMPLEMENTATION
#include <ApprovalTests.hpp>
#include "TestTracking.h"

TEST_CASE("Approval in module two")
{
    recordModuleTest(2);
    ApprovalTests::Approvals::verify("module two", ApprovalTests::Options().withReporter(
                                                      ApprovalTests::QuietReporter()));
}
