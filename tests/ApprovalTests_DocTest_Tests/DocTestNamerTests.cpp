#include "doctest.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "Approvals.h"

TEST_CASE("ItCanGiveYouTheSpecName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    SUBCASE("andSectionNames")
    {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        SUBCASE("andEvenMoreSectionNames")
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
    ApprovalTests::Approvals::verify("hello world");
}
