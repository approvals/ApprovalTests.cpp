#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include "CppUTest/TestHarness.h"

using namespace ApprovalTests;

namespace
{
    void checkEndsWith(const std::string& value, const std::string& ending)
    {
        std::string message = "\n" + value + "\nshould end with\n" + ending + '\n';
        CHECK_TEXT(StringUtils::endsWith(value, ending), message.c_str());
    }

    void checkEndsWithIgnoringCase(const std::string& value, const std::string& ending)
    {
        checkEndsWith(StringUtils::toLower(value), StringUtils::toLower(ending));
    }

    void checkContains(const std::string& inText, const std::string& find)
    {
        std::string message = "\n" + inText + "\nshould contain\n" + find + '\n';
        CHECK_TEXT(StringUtils::contains(inText, find), message.c_str());
    }
}

TEST_GROUP(NamerTestGroup){};

TEST(NamerTestGroup, ItCanGiveYouTheSpecName)
{

    ApprovalTestNamer namer;
    STRCMP_EQUAL(namer.getTestName().c_str(), "NamerTestGroup.ItCanGiveYouTheSpecName");
}

TEST(NamerTestGroup, ItCanGiveYouTheTestFileName)
{
    ApprovalTestNamer namer;
    STRCMP_EQUAL(namer.getFileName().c_str(), "CppUTestNamerTests");
}

TEST(NamerTestGroup, TestProperNameCaseOnWindows)
{
    if (SystemUtils::isWindowsOs())
    {
        ApprovalTestNamer namer;
        auto test = ApprovalTestNamer::currentTest();
        test.setFileName(StringUtils::toLower(test.getFileName()));
        ApprovalTestNamer::currentTest(&test);
        STRCMP_EQUAL(namer.getFileName().c_str(), "CppUTestNamerTests");
    }
}

TEST(NamerTestGroup, ItCanGiveYouTheTestDirectory)
{
    // This should work with CaseSensitive::Yes.
    // However, it would fail when run in Visual Studio 2017 as lower-case source-file names are returned.
    // We've fixed this for filenames, but not directory names, so this test ignores case.
    // See https://stackoverflow.com/questions/49068785/how-to-find-the-filename-from-a-c11-stat-objects-file-serial-number-on-window
    auto suppress_subdirectory = Approvals::useApprovalsSubdirectory("");
    ApprovalTestNamer namer;
    auto sep = SystemUtils::getDirectorySeparator();
    checkEndsWithIgnoringCase(namer.getDirectory(),
                              sep + "CppUTest_Tests" + sep + "namers" + sep);
}

TEST(NamerTestGroup, ItIncludesFileContextAndSpecNames)
{
    ApprovalTestNamer namer;
    auto sep = SystemUtils::getDirectorySeparator();

    std::string expectedBaseName = sep + "CppUTestNamerTests.NamerTestGroup."
                                         "ItIncludesFileContextAndSpecNames";

    checkEndsWith(namer.getApprovedFile(".txt"), expectedBaseName + ".approved.txt");
    checkEndsWith(namer.getReceivedFile(".txt"), expectedBaseName + ".received.txt");
}

TEST(NamerTestGroup, UseSubDirectory)
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("approved_files");
    auto namer = Approvals::getDefaultNamer();
    checkContains(namer->getApprovedFile(".txt"), "approved_files");
}

TEST(NamerTestGroup, UseSubDirectoriesCleanToPreviousResults)
{
    auto subdirectory = Approvals::useApprovalsSubdirectory("outer");
    auto namer = Approvals::getDefaultNamer();

    {
        auto subdirectory2 = Approvals::useApprovalsSubdirectory("inner");
        checkContains(namer->getApprovedFile(".txt"), "inner");
    }

    checkContains(namer->getApprovedFile(".txt"), "outer");
}
