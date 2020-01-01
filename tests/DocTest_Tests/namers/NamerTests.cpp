#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalNamer.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/namers/NamerFactory.h"
#include "ApprovalTests/Approvals.h"

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
        auto default_namer_disposer = Approvals::useAsDefaultNamer([](){return std::make_shared<FakeNamer>();});
        // end-snippet
        auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
        REQUIRE(result == "my.approved");
    }
    auto result = Approvals::getDefaultNamer()->getApprovedFile(".txt");
    REQUIRE(StringUtils::endsWith(result, "NamerTests.Registering_default_Namer.approved.txt"));
}

void require_ends_with(const std::string& text, const std::string& endsWith)
{
    INFO(text << "\ndidn't end with\n" << endsWith);
    REQUIRE(StringUtils::endsWith(text, endsWith));
}

TEST_CASE("SeparateApprovedAndReceivedDirectoriesNamer")
{
    // begin-snippet: register_separate_directories_namer
    auto default_namer_disposer = SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer();
    // end-snippet

    auto namer = Approvals::getDefaultNamer();
    require_ends_with(namer->getApprovedFile(".txt"), "approved" + SystemUtils::getDirectorySeparator() +
                                                      "NamerTests.SeparateApprovedAndReceivedDirectoriesNamer.txt");
    require_ends_with(namer->getReceivedFile(".txt"), "received" + SystemUtils::getDirectorySeparator() +
                                                      "NamerTests.SeparateApprovedAndReceivedDirectoriesNamer.txt");
}

TEST_CASE( "AdditionalSections" )
{
    auto namer = Approvals::getDefaultNamer();

    {
        auto section_namer = NamerFactory::appendToOutputFilename("case1");
        require_ends_with(namer->getApprovedFile(".txt"), "NamerTests.AdditionalSections.case1.approved.txt");
    }
    {
        auto section_namer = NamerFactory::appendToOutputFilename("case2");
        require_ends_with(namer->getApprovedFile(".txt"), "NamerTests.AdditionalSections.case2.approved.txt");
    }
    require_ends_with(namer->getApprovedFile(".txt"), "NamerTests.AdditionalSections.approved.txt");
}
