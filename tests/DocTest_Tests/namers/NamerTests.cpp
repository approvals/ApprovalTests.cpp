#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/utilities/SystemUtils.h"

//#include <filesystem>
#include <iostream>
#include <memory>

using namespace ApprovalTests;

class FakeNamer : public ApprovalNamer
{
    virtual std::string getApprovedFile(std::string /*extensionWithDot*/) const override
    {
        return "my.approved";
    }
    virtual std::string getReceivedFile(std::string /*extensionWithDot*/) const override
    {
        return "my.received";
    }
};

TEST_CASE("Registering default Namer")
{
    {
        // begin-snippet: register_default_namer
        auto default_namer_disposer =
            Approvals::useAsDefaultNamer([]() { return std::make_shared<FakeNamer>(); });
        // end-snippet
        auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
        REQUIRE(result == "my.approved");
    }
    auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    REQUIRE(StringUtils::endsWith(result,
                                  "NamerTests.Registering_default_Namer.approved.txt"));
}

void require_ends_with(const std::string& text, const std::string& endsWith)
{
    INFO("\n'" << text << "'\ndidn't end with\n'" << endsWith << "'"
               << "\n");
    REQUIRE(StringUtils::endsWith(text, endsWith));
}

TEST_CASE("SeparateApprovedAndReceivedDirectoriesNamer")
{
    // begin-snippet: register_separate_directories_namer
    auto default_namer_disposer =
        SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer();
    // end-snippet

    auto namer = Approvals::getDefaultNamer();
    require_ends_with(namer->getApprovedFile(".txt"),
                      "approved" + SystemUtils::getDirectorySeparator() +
                          "NamerTests.SeparateApprovedAndReceivedDirectoriesNamer.txt");
    require_ends_with(namer->getReceivedFile(".txt"),
                      "received" + SystemUtils::getDirectorySeparator() +
                          "NamerTests.SeparateApprovedAndReceivedDirectoriesNamer.txt");

    Approvals::verify("Verify that approved/ and received/ are created automatically");
}

TEST_CASE("AdditionalSections")
{
    auto namer = Approvals::getDefaultNamer();

    {
        auto section_namer = NamerFactory::appendToOutputFilename("case1");
        require_ends_with(namer->getApprovedFile(".txt"),
                          "NamerTests.AdditionalSections.case1.approved.txt");
    }
    {
        auto section_namer = NamerFactory::appendToOutputFilename("case2");
        require_ends_with(namer->getApprovedFile(".txt"),
                          "NamerTests.AdditionalSections.case2.approved.txt");
    }
    require_ends_with(namer->getApprovedFile(".txt"),
                      "NamerTests.AdditionalSections.approved.txt");
}

struct TestNameResetter
{
    TestNameResetter() : oldPrefix_(TestName::directoryPrefix)
    {
    }
    ~TestNameResetter()
    {
        TestName::directoryPrefix = oldPrefix_;
    }
    std::string oldPrefix_;
};

std::string getFileName()
{
    return "ApprovalTests.cpp/tests/DocTest_Tests/namers/NamerTests.cpp";
}

TEST_CASE("Find from parent")
{
    TestNameResetter resetter;
    TestName name;
    std::string junkDir = "/non/existing/directory/";
    TestName::directoryPrefix = junkDir;
    auto file = name.checkParentDirectoriesForFile(getFileName());
    //    std::cout << "Working directory = " << std::filesystem::absolute(".") << std::endl;
    std::cout << "File name = " << file << std::endl;
    CHECK(FileUtils::fileExists(file));
    CHECK(TestName::directoryPrefix != junkDir);
}

TEST_CASE("Sanitizer <3 fileNames")
{
    {
        auto useFileNameSanitizer_disposer =
            Approvals::useFileNameSanitizer([](std::string incoming) {
                return StringUtils::replaceAll(incoming, " <3 ", "_loves_");
            });
        auto namer = Approvals::getDefaultNamer();
        CHECK(StringUtils::endsWith(namer->getApprovedFile(".txt"),
                                    "Sanitizer_loves_fileNames.approved.txt"));
    }
    {
        auto namer = Approvals::getDefaultNamer();
        CHECK(StringUtils::endsWith(namer->getApprovedFile(".txt"),
                                    "Sanitizer__3_fileNames.approved.txt"));
    }
}

TEST_CASE("Check non-existent file reports misconfigured build")
{

    TestNameResetter resetter;
    TestName name;
    TestName::directoryPrefix = "";
    std::string nonExistentPath = "/I/Do/Not/Exist.cpp";
    name.setFileName(nonExistentPath);
    try
    {
        auto file = name.getFileName(); // Simulate no tests having yet been run
        std::cout << "File name = " << file << std::endl;
        FAIL("TestName::getFileName() on non-existent file should have thrown");
    }
    catch (const std::runtime_error& e)
    {
        std::string exceptionText = e.what();
        CHECK(StringUtils::contains(exceptionText, nonExistentPath));
        CHECK(StringUtils::contains(
            exceptionText, "There seems to be a problem with your build configuration."));
    }
}

TEST_CASE("Test Root Directory Help Message")
{
    Approvals::verify(HelpMessages::getUnconfiguredRootDirectory());
}
