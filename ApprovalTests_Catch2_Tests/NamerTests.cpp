#include "Catch.hpp"
#include "../ApprovalTests/namers/ApprovalTestNamer.h"
#include "../ApprovalTests/StringUtils.h"

using namespace std;
using Catch::Matchers::EndsWith;

TEST_CASE("ItCanGiveYouTheSpecName") {

    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    SECTION("andSectionNames") {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        SECTION("andEvenMoreSectionNames") {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames.andEvenMoreSectionNames");
        }
    }
}


TEST_CASE("ItCanGiveYouTheTestFileName") {
    ApprovalTestNamer namer;
    REQUIRE(namer.getFileName() == "NamerTests");
}


TEST_CASE("TestProperNameCaseOnWindows") {
    if (SystemUtils::isWindowsOs())
    {
        ApprovalTestNamer namer;
        auto test = namer.currentTest();
        test.fileName = StringUtils::toLower(test.fileName);
        namer.currentTest(&test);
        REQUIRE(namer.getFileName() == "NamerTests");
    }
}


TEST_CASE("ItCanGiveYouTheTestDirectory") {
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(namer.getDirectory(), EndsWith(__ + "ApprovalTests_Catch2_Tests" + __));
}


TEST_CASE("ItIncludesFileContextAndSpecNames") {
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();

    REQUIRE_THAT(namer.getApprovedFile(".txt"),
        EndsWith(__ + "ApprovalTests_Catch2_Tests" + __ + "NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
    REQUIRE_THAT(namer.getReceivedFile(".txt"),
        EndsWith(__ + "ApprovalTests_Catch2_Tests" + __ + "NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}


