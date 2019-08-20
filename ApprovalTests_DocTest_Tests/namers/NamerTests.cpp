#include "doctest.h"
#include "ApprovalTests/namers/ApprovalNamer.h"
#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"
#include "ApprovalTests/Approvals.h"

#include <memory>

class FakeNamer : public ApprovalNamer
{
    virtual string getApprovedFile(string /*extensionWithDot*/) override
    {
        return "my.approved";
    }
    virtual string getReceivedFile(string /*extensionWithDot*/) override 
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
