#include "Catch.hpp"

#include "ApprovalTests/reporters/BlockingReporter.h"

TEST_CASE("Ensure this compiles")
{
    BlockingReporter::onMachineNamed("THIS MACHINE");
    BlockingReporter::onMachinesNotNamed("THIS MACHINE");
}
