#include "integrations/catch/Catch2Include.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/Approvals.h"

using Catch::Matchers::EndsWith;

using namespace ApprovalTests;

namespace
{
    // Between catch2 v2 and catch2 v3 the Matcher::Contains has changed.
    // In v3 Matcher::ContainsSubstring needs to be used for string types.
    //
    // The two functions in this anonymous namesace dispatch based on the selected catch2
    // version.

    void check_contains(std::string const& input, std::string const& expectedSubstring)
    {
#ifdef APPROVAL_TESTS_USE_CATCH2V3
        REQUIRE_THAT(input, Catch::Matchers::ContainsSubstring(expectedSubstring));
#else
        REQUIRE_THAT(input, Catch::Matchers::Contains(expectedSubstring));
#endif
    }

    void check_contains_not(std::string const& input,
                            std::string const& expectedSubstring)
    {
#ifdef APPROVAL_TESTS_USE_CATCH2V3
        REQUIRE_THAT(input, !Catch::Matchers::ContainsSubstring(expectedSubstring));
#else
        REQUIRE_THAT(input, !Catch::Matchers::Contains(expectedSubstring));
#endif
    }
}

TEST_CASE("ItCanGiveYouTheSpecName")
{

    const ApprovalTestNamer namer;
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
    const ApprovalTestNamer namer;
    REQUIRE(namer.getSourceFileName() == "Catch2NamerTests");
}

TEST_CASE("TestProperNameCaseOnWindows")
{
    if (SystemUtils::isWindowsOs())
    {
        const ApprovalTestNamer namer;
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
    const ApprovalTestNamer namer;
    auto __ = SystemUtils::getDirectorySeparator();
    REQUIRE_THAT(
        namer.getDirectory(),
        EndsWith(__ + "Catch2_Tests" + __ + "namers" + __, Catch::CaseSensitive::No));
}

TEST_CASE("ItIncludesFileContextAndSpecNames")
{
    const ApprovalTestNamer namer;
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
    const std::vector<std::string> names = {"CleanUpFilenameTransforms",
                                            "Spaces In File \\"};
    Approvals::verifyAll("File Names",
                         names,
                         [&](const std::string& name, std::ostream& s) {
                             s << name << " => "
                               << ApprovalTestNamer::convertToFileName(name);
                         });
}

TEST_CASE("Use sub-directory")
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("approved_files");
    const auto namer = Approvals::getDefaultNamer();
    check_contains(namer->getApprovedFile(".txt"), "approved_files");
}

TEST_CASE("Use sub-directories clean to previous results")
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("outer");
    const auto namer = Approvals::getDefaultNamer();

    {
        auto subdirectory2 = Approvals::useApprovalsSubdirectory("inner");
        check_contains(namer->getApprovedFile(".txt"), "inner");
    }

    check_contains(namer->getApprovedFile(".txt"), "outer");
}

TEST_CASE("Tags not included in file name", "[tag_name]")
{
    const auto namer = Approvals::getDefaultNamer();
    check_contains_not(namer->getApprovedFile(".txt"), "tag_name");
}
