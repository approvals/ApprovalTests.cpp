#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/HelpMessages.h"
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

TEST_CASE("HelpMessageForIncorrectBoostUTConfig")
{
    // This is the error message that is issued if the build
    // is does not satisfy all the requirements for Boost.UT
    // with ApprovalTests.cpp
    Approvals::verify(HelpMessages::getMisconfiguredBuildHelp("unknown"));
}
