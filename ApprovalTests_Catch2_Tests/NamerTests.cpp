#include "../ApprovalTests/Catch2Approvals.h"


using namespace std;
using Catch::Matchers::EndsWith;

TEST_CASE("ItCanGiveYouTheSpecName") {

    ApprovalNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    SECTION("andSectionNames") {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        SECTION("andEvenMoreSectionNames") {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames.andEvenMoreSectionNames");
        }
    }
}


TEST_CASE("ItCanGiveYouTheTestFileName") {
    ApprovalNamer namer;
    REQUIRE(namer.getFileName() == "NamerTests");
}


TEST_CASE("ItCanGiveYouTheTestDirectory") {
    ApprovalNamer namer;
    REQUIRE_THAT(namer.getDirectory(), EndsWith("/ApprovalTests_Catch2_Tests/"));
}


TEST_CASE("ItIncludesFileContextAndSpecNames") {
    ApprovalNamer namer;
    REQUIRE_THAT(namer.getApprovedFile(".txt"),
                 EndsWith("/ApprovalTests_Catch2_Tests/NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
    REQUIRE_THAT(namer.getReceivedFile(".txt"),
                 EndsWith("/ApprovalTests_Catch2_Tests/NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}


