#include "doctest/doctest.h"

#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/utilities/MachineBlocker.h"

TEST_CASE("Blocks in this environment")
{
    auto machineName = ApprovalTests::SystemUtils::getMachineName();
    auto blocker = ApprovalTests::MachineBlocker::onMachineNamed(machineName);
    REQUIRE(blocker.isBlockingOnThisMachine() == true);
}

TEST_CASE("Does not block in this environment")
{
    auto machineName = ApprovalTests::SystemUtils::getMachineName();
    auto blocker = ApprovalTests::MachineBlocker::onMachinesNotNamed(machineName);
    REQUIRE(blocker.isBlockingOnThisMachine() == false);
}

// begin-snippet: machine_specific_test_runner
TEST_CASE("Only run this test on John's machine")
{
    auto blocker = ApprovalTests::MachineBlocker::onMachinesNotNamed("JOHNS_MACHINE");
    if (blocker.isBlockingOnThisMachine())
    {
        return;
    }
    // Write tests here that depend on John's environment.
    REQUIRE(ApprovalTests::SystemUtils::getMachineName() == "JOHNS_MACHINE");
}
// end-snippet
