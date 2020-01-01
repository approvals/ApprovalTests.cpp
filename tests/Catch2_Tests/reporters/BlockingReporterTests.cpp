#include "catch2/catch.hpp"

#include "ApprovalTests/reporters/BlockingReporter.h"

using namespace ApprovalTests;

TEST_CASE("Ensure this compiles")
{
    BlockingReporter::onMachineNamed("THIS MACHINE");
    BlockingReporter::onMachinesNotNamed("THIS MACHINE");
}
