#include "Catch.hpp"
#include <ApprovalTests/StringUtils.h>


TEST_CASE("TestLowerCase") {
    REQUIRE(StringUtils::toLower("MiXeD CaSe") == "mixed case");
}
