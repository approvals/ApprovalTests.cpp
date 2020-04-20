#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

// <iostream> is needed to fix linker error on XCode Release builds:
#include <iostream>

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
