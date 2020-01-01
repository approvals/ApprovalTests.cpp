#include "ApprovalTests/Approvals.h"
#include "doctest.h"

using namespace ApprovalTests;
TEST_CASE("HelpMessage")
{
    Approvals::verify(ApprovalTestNamer::getMisconfiguredMainHelp());
}

TEST_CASE("HelpMessageForIncorrectBuildConfig")
{
    Approvals::verify(TestName::getMisconfiguredBuildHelp(
        "../../../tests/Catch1_Tests/ApprovalsTests.cpp"));
}
