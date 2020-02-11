#include "doctest/doctest.h"

#include "ApprovalTests/reporters/BlockingReporter.h"

using namespace ApprovalTests;

TEST_CASE("Ensure this compiles")
{
    BlockingReporter::onMachineNamed("THIS MACHINE");
    BlockingReporter::onMachinesNotNamed("THIS MACHINE");
}
