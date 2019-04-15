#include "Catch.hpp"

#include "ApprovalTests/SystemUtils.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/BlockingReporter.h"

TEST_CASE("Blocks in this environment")
{
    auto machineName = SystemUtils::getMachineName();
    auto reporter = BlockingReporter::onMachineNamed(machineName);
    REQUIRE(reporter->report("r.txt", "a.txt") == true);
}

TEST_CASE("Does not block in this environment")
{
    auto machineName = SystemUtils::getMachineName();
    auto reporter = BlockingReporter::onMachinesNotNamed(machineName);
    REQUIRE(reporter->report("r.txt", "a.txt") == false);

    auto frontLoadedReportDisposer = Approvals::useAsFrontLoadedReporter(
        BlockingReporter::onMachinesNotNamed("MyCIMachineName") );
}
