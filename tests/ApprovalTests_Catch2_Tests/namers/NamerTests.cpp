#include "Catch.hpp"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/StringUtils.h"
#include "ApprovalTests/Approvals.h"
#include "Approvals.h"
#include "StringUtils.h"

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
        test.setFileName(ApprovalTests::StringUtils::toLower(test.getFileName()));
        namer.currentTest(&test);
        REQUIRE(namer.getFileName() == "NamerTests");
    }
}


TEST_CASE("ItCanGiveYouTheTestDirectory") {
    // This should work with CaseSensitive::Yes.
    // However, it would fail when run in Visual Studio 2017 as lower-case source-file names are returned.
    // We've fixed this for filenames, but not directory names, so this test ignores case.
    // See https://stackoverflow.com/questions/49068785/how-to-find-the-filename-from-a-c11-stat-objects-file-serial-number-on-window
    auto suppress_subdirectory = ApprovalTests::Approvals::useApprovalsSubdirectory("");
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(namer.getDirectory(), EndsWith(__ + "ApprovalTests_Catch2_Tests" + __ + "namers" + __, Catch::CaseSensitive::No));
}


TEST_CASE("ItIncludesFileContextAndSpecNames") {
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();

    REQUIRE_THAT(namer.getApprovedFile(".txt"),
        EndsWith(__ + "NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
    REQUIRE_THAT(namer.getReceivedFile(".txt"),
        EndsWith(__ + "NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}


TEST_CASE("Clean Up Filename Transforms")
{
    std::vector<std::string> names = { "CleanUpFilenameTransforms", "Spaces In File \\" };
    ApprovalTests::Approvals::verifyAll("File Names", names, [&](std::string name, std::ostream &s) {s << name << " => " << ApprovalTestNamer::convertToFileName(name); });
}

TEST_CASE("Use sub-directory")
{
    auto subdirectory = ApprovalTests::Approvals::useApprovalsSubdirectory("approved_files");
    auto namer = ApprovalTests::Approvals::getDefaultNamer();
    REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "approved_files" ) );
}

TEST_CASE("Use sub-directories clean to previous results")
{
    auto subdirectory = ApprovalTests::Approvals::useApprovalsSubdirectory("outer");
    auto namer = ApprovalTests::Approvals::getDefaultNamer();
    
    {
        auto subdirectory2 = ApprovalTests::Approvals::useApprovalsSubdirectory("inner");
        REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "inner" ) );
    }
    
    REQUIRE_THAT( namer->getApprovedFile(".txt"), Catch::Matchers::Contains( "outer" ) );
}
