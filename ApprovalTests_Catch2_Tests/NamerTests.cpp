#include "Catch.hpp"
#include "../ApprovalTests/namers/ApprovalNamer.h"
#include "../ApprovalTests/StringUtils.h"

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


TEST_CASE("TestProperNameCaseOnWindows") {
    if (SystemUtils::isWindowsOs())
    {
        ApprovalNamer namer;
        auto test = namer.currentTest();
        test.fileName = StringUtils::toLower(test.fileName);
        namer.currentTest(&test);
        REQUIRE(namer.getFileName() == "NamerTests");
    }
}


TEST_CASE("ItCanGiveYouTheTestDirectory") {
    ApprovalNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(namer.getDirectory(), EndsWith(__ + "ApprovalTests_Catch2_Tests" + __));
}


TEST_CASE("ItIncludesFileContextAndSpecNames") {
    ApprovalNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();

    REQUIRE_THAT(namer.getApprovedFile(".txt"),
        EndsWith(__ + "ApprovalTests_Catch2_Tests" + __ + "NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
    REQUIRE_THAT(namer.getReceivedFile(".txt"),
        EndsWith(__ + "ApprovalTests_Catch2_Tests" + __ + "NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}


