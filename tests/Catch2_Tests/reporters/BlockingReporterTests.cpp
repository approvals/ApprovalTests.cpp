#include "Catch.hpp"

#include "ApprovalTests/reporters/BlockingReporter.h"

TEST_CASE("Ensure this compiles")
{
    ApprovalTests::BlockingReporter::onMachineNamed("THIS MACHINE");
    ApprovalTests::BlockingReporter::onMachinesNotNamed("THIS MACHINE");
}
