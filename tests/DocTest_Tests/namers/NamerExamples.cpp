#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "../utilities/TestUtils.h"

#include <memory>

class FakeNamer : public ApprovalTests::ApprovalNamer
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
        auto default_namer_disposer = ApprovalTests::Approvals::useAsDefaultNamer(
            []() { return std::make_shared<FakeNamer>(); });
        // end-snippet
        auto result =
            ApprovalTests::Approvals::getDefaultNamer()->getApprovedFile(".txt");
        REQUIRE(result == "my.approved");
    }
    auto result = ApprovalTests::Approvals::getDefaultNamer()->getApprovedFile(".txt");
    REQUIRE(ApprovalTests::StringUtils::endsWith(
        result, "NamerExamples.Registering_default_Namer.approved.txt"));
}

TEST_CASE("SeparateApprovedAndReceivedDirectoriesNamer")
{
    // begin-snippet: register_separate_directories_namer
    auto default_namer_disposer =
        ApprovalTests::SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer();
    // end-snippet

    auto namer = ApprovalTests::Approvals::getDefaultNamer();
    require_ends_with(
        namer->getApprovedFile(".txt"),
        "approved" + ApprovalTests::SystemUtils::getDirectorySeparator() +
            "NamerExamples.SeparateApprovedAndReceivedDirectoriesNamer.txt");
    require_ends_with(
        namer->getReceivedFile(".txt"),
        "received" + ApprovalTests::SystemUtils::getDirectorySeparator() +
            "NamerExamples.SeparateApprovedAndReceivedDirectoriesNamer.txt");

    ApprovalTests::Approvals::verify(
        "Verify that approved/ and received/ are created automatically");
}

// begin-snippet: useFileNameSanitizer
TEST_CASE("Sanitizer <3 fileNames")
{
    {
        auto disposer =
            ApprovalTests::Approvals::useFileNameSanitizer([](std::string incoming) {
                return ApprovalTests::StringUtils::replaceAll(
                    incoming, " <3 ", "_loves_");
            });
        // end-snippet
        auto namer = ApprovalTests::Approvals::getDefaultNamer();
        CHECK(ApprovalTests::StringUtils::endsWith(
            namer->getApprovedFile(".txt"), "Sanitizer_loves_fileNames.approved.txt"));
    }
    {
        auto namer = ApprovalTests::Approvals::getDefaultNamer();
        CHECK(ApprovalTests::StringUtils::endsWith(
            namer->getApprovedFile(".txt"), "Sanitizer__3_fileNames.approved.txt"));
    }
}
