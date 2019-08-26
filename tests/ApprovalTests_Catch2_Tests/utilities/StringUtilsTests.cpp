#include "Catch.hpp"
#include "ApprovalTests/StringUtils.h"
#include "StringUtils.h"


TEST_CASE("TestLowerCase") {
    REQUIRE(ApprovalTests::StringUtils::toLower("MiXeD CaSe") == "mixed case");
}
