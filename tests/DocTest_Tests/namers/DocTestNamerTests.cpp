#include "doctest/doctest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("ItCanGiveYouTheSpecName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    SUBCASE("andSectionNames")
    {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        SUBCASE("andEvenMoreSectionNames")
        {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames."
                                           "andEvenMoreSectionNames");
        }
    }
}

TEST_CASE("ItCanGiveYouTheTestFileName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getSourceFileName() == "DocTestNamerTests");
}

TEST_CASE("It can verify tests with spaces")
{
    Approvals::verify("hello world");
}
