#include "ApprovalTests/Approvals.h"
#include "doctest/doctest.h"

using namespace ApprovalTests;
TEST_CASE("HelpMessage")
{
    Approvals::verify(HelpMessages::getMisconfiguredMainHelp());
}

TEST_CASE("HelpMessageForIncorrectBuildConfig")
{
    Approvals::verify(HelpMessages::getMisconfiguredBuildHelp(
        "../../../tests/Catch2_Tests/ApprovalsTests.cpp"));
}
