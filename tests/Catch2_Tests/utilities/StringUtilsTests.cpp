#include "catch2/catch.hpp"
#include "ApprovalTests/utilities/StringUtils.h"

using namespace ApprovalTests;

TEST_CASE("TestLowerCase")
{
    REQUIRE(StringUtils::toLower("MiXeD CaSe") == "mixed case");
}
