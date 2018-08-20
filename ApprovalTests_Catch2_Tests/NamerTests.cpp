#include "Catch.hpp"
#include "../ApprovalTests/namers/ApprovalTestNamer.h"
#include "../ApprovalTests/StringUtils.h"
#include "../ApprovalTests/Approvals.h"

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
	// This should work with CaseSensitive::Yes.
	// However, it would fail when run in Visual Studio 2017 as lower-case source-file names are returned.
	// We've fixed this for filenames, but not directory names, so this test ignores case.
	// See https://stackoverflow.com/questions/49068785/how-to-find-the-filename-from-a-c11-stat-objects-file-serial-number-on-window
	ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(namer.getDirectory(), EndsWith(__ + "ApprovalTests_Catch2_Tests" + __, Catch::CaseSensitive::No));
}


TEST_CASE("ItIncludesFileContextAndSpecNames") {
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();

	REQUIRE_THAT(namer.getApprovedFile(".txt"),
		EndsWith(__ + "NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
	REQUIRE_THAT(namer.getReceivedFile(".txt"),
		EndsWith(__ + "NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}


TEST_CASE("CleanUpFilenameTransforms")
{
    std::vector<std::string> names = { "CleanUpFilenameTransforms", "Spaces In File \\" };
    Approvals::verifyAll("File Names", names, [&](std::string name, std::ostream &s) {s << name << " => " << ApprovalTestNamer::convertToFileName(name); });
}
