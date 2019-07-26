#include "doctest.hpp"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("ItCanGiveYouTheSpecName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    DOCTEST_SUBCASE("andSectionNames")
    {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        DOCTEST_SUBCASE("andEvenMoreSectionNames")
        {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames.andEvenMoreSectionNames");
        }
    }
}

TEST_CASE("ItCanGiveYouTheTestFileName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getFileName() == "DocTestNamerTests");
}

TEST_CASE("It can verify tests with spaces")
{
    Approvals::verify("hello world");
}
