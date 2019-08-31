#include "ApprovalTests/Approvals.h"
#include "doctest.h"

using namespace ApprovalTests;
TEST_CASE("HelpMessage")
{
    Approvals::verify( ApprovalTestNamer::getMisconfiguredMainHelp() );
}
