#include "doctest/doctest.h"
#include "ApprovalTests/utilities/StringUtils.h"

using namespace ApprovalTests;

TEST_CASE("BeginsWith")
{
    std::string text("The Quick Brown Fox");
    CHECK(StringUtils::startsWith(text, "T") == true);
    CHECK(StringUtils::startsWith(text, "The") == true);
    CHECK(StringUtils::startsWith(text, "The Q") == true);
    CHECK(StringUtils::startsWith(text, text) == true);

    CHECK(StringUtils::startsWith(text, "F") == false);
    CHECK(StringUtils::startsWith(text, "Quick Brown") == false);
    CHECK(StringUtils::startsWith(text, "That") == false);

    CHECK(StringUtils::startsWith("", "That") == false);
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
