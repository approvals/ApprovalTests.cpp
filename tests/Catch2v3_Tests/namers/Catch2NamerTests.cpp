#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/Approvals.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using Catch::Matchers::EndsWith;

using namespace ApprovalTests;

TEST_CASE("ItCanGiveYouTheSpecName")
{

    ApprovalTestNamer namer;
    REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName");

    SECTION("andSectionNames")
    {
        REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames");
        SECTION("andEvenMoreSectionNames")
        {
            REQUIRE(namer.getTestName() == "ItCanGiveYouTheSpecName.andSectionNames."
                                           "andEvenMoreSectionNames");
        }
    }
}

TEST_CASE("ItCanGiveYouTheTestFileName")
{
    ApprovalTestNamer namer;
    REQUIRE(namer.getSourceFileName() == "Catch2NamerTests");
}

TEST_CASE("TestProperNameCaseOnWindows")
{
    if (SystemUtils::isWindowsOs())
    {
        ApprovalTestNamer namer;
        auto test = namer.currentTest();
        test.setFileName(StringUtils::toLower(test.getFileName()));
        namer.currentTest(&test);
        REQUIRE(namer.getSourceFileName() == "Catch2NamerTests");
    }
}

TEST_CASE("ItCanGiveYouTheTestDirectory")
{
    // This should work with CaseSensitive::Yes.
    // However, it would fail when run in Visual Studio 2017 as lower-case source-file names are returned.
    // We've fixed this for filenames, but not directory names, so this test ignores case.
    // See https://stackoverflow.com/questions/49068785/how-to-find-the-filename-from-a-c11-stat-objects-file-serial-number-on-window
    auto suppress_subdirectory = Approvals::useApprovalsSubdirectory("");
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(
        namer.getDirectory(),
        EndsWith(__ + "Catch2v3_Tests" + __ + "namers" + __, Catch::CaseSensitive::No));
}

TEST_CASE("ItIncludesFileContextAndSpecNames")
{
    ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();

    REQUIRE_THAT(
        namer.getApprovedFile(".txt"),
        EndsWith(__ + "Catch2NamerTests.ItIncludesFileContextAndSpecNames.approved.txt"));
    REQUIRE_THAT(
        namer.getReceivedFile(".txt"),
        EndsWith(__ + "Catch2NamerTests.ItIncludesFileContextAndSpecNames.received.txt"));
}

TEST_CASE("Clean Up Filename Transforms")
{
    std::vector<std::string> names = {"CleanUpFilenameTransforms", "Spaces In File \\"};
    Approvals::verifyAll(
        "File Names", names, [&](const std::string& name, std::ostream& s) {
            s << name << " => " << ApprovalTestNamer::convertToFileName(name);
        });
}

TEST_CASE("Use sub-directory")
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("approved_files");
    auto namer = Approvals::getDefaultNamer();
    REQUIRE_THAT(namer->getApprovedFile(".txt"),
                 Catch::Matchers::ContainsSubstring("approved_files"));
}

TEST_CASE("Use sub-directories clean to previous results")
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("outer");
    auto namer = Approvals::getDefaultNamer();

    {
        auto subdirectory2 = Approvals::useApprovalsSubdirectory("inner");
        REQUIRE_THAT(namer->getApprovedFile(".txt"),
                     Catch::Matchers::ContainsSubstring("inner"));
    }

    REQUIRE_THAT(namer->getApprovedFile(".txt"),
                 Catch::Matchers::ContainsSubstring("outer"));
}

TEST_CASE("Tags not included in file name", "[tag_name]")
{
    auto namer = Approvals::getDefaultNamer();
    REQUIRE_THAT(namer->getApprovedFile(".txt"),
                 !Catch::Matchers::ContainsSubstring("tag_name"));
}
