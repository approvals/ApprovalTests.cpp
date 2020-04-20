#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

// <iostream> is needed to fix linker error on XCode Release builds:
#include <iostream>
#include <ApprovalTests/Approvals.h>

using namespace ApprovalTests;

TEST_CASE("Input with single GUID")
{
    auto input = "2fd78d4a-ad49-447d-96a8-deda585a9aa5 and normal text";
    auto output = Scrubbers::scrubGuid(input);
    REQUIRE(output == "guid_1 and normal text");
}

TEST_CASE("Input with no GUIDs")
{
    auto input = "";
    auto output = Scrubbers::scrubGuid(input);
    REQUIRE(output == "");
}

TEST_CASE("Input with non-GUID")
{
    std::string input = "hello world";
    auto output = Scrubbers::scrubGuid(input);
    REQUIRE(output == input);
}

TEST_CASE("Input with non-GUID")
{

    std::string input = R"(
{
    child: {
        id: b34b4da8-090e-49d8-bd35-7e79f633a2ea
        parent1: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
        parent2: 05f77de3-3790-4d45-b045-def96c9cd371
    }
    person: {
        name: mom
        id: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
    }
    person: {
        name: dad
        id: 05f77de3-3790-4d45-b045-def96c9cd371
    }
}
)";
    auto output = Scrubbers::scrubGuid(input);
    Approvals::verifyScrubbed(input, Scrubbers::scrubGuid);
}
