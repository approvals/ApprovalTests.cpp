#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

using namespace ApprovalTests;

TEST_CASE("Input with single GUID")
{
    auto input = "2fd78d4a-ad49-447d-96a8-deda585a9aa5";
    auto output = Scrubbers::scrubGuid(input);
    REQUIRE(output == "guid_1");
}

TEST_CASE("Input with no GUIDs")
{
    auto input = "";
    auto output = Scrubbers::scrubGuid(input);
    //    REQUIRE(output == "");
}
