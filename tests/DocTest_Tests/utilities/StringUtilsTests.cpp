#include "doctest/doctest.h"
#include "ApprovalTests/utilities/StringUtils.h"

using namespace ApprovalTests;

TEST_CASE("BeginsWith")
{
    std::string text("The Quick Brown Fox");
    CHECK(StringUtils::beginsWith(text, "T") == true);
    CHECK(StringUtils::beginsWith(text, "The") == true);
    CHECK(StringUtils::beginsWith(text, "The Q") == true);
    CHECK(StringUtils::beginsWith(text, text) == true);

    CHECK(StringUtils::beginsWith(text, "F") == false);
    CHECK(StringUtils::beginsWith(text, "Quick Brown") == false);
    CHECK(StringUtils::beginsWith(text, "That") == false);

    CHECK(StringUtils::beginsWith("", "That") == false);
}

TEST_CASE("EndsWith")
{
    std::string text("The Quick Brown Fox");
    CHECK(StringUtils::endsWith(text, text) == true);
}

TEST_CASE("TestLowerCase")
{
    REQUIRE(StringUtils::toLower("MiXeD CaSe") == "mixed case");
}

TEST_CASE("Trim")
{
    REQUIRE(StringUtils::trim("    hei    ") == "hei");
}
