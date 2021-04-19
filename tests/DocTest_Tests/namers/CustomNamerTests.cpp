#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("Test StringTemplates")
{
    // begin-snippet: templated_custom_namer_example
    TemplatedCustomNamer namer("/my/source/directory/{ApprovedOrReceived}/"
                               "{TestFileName}.{TestCaseName}.{FileExtension}");
    // end-snippet

    CHECK(namer.getApprovedFile(".txt") ==
          "/my/source/directory/approved/CustomNamerTests.Test_StringTemplates.txt");
    CHECK(namer.getReceivedFile(".txt") ==
          "/my/source/directory/received/CustomNamerTests.Test_StringTemplates.txt");
}

TEST_CASE("Test Namer Injection")
{
    // begin-snippet: templated_custom_namer_injection
    auto default_namer_disposer = Approvals::useAsDefaultNamer(
        []()
        {
            return std::make_shared<TemplatedCustomNamer>(
                "{TestSourceDirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
        });
    // end-snippet

    Approvals::verify("Hello");
}

// TODO Move Path impl to .cpp
// TODO Try it on an embedded device - or ask someone else to!
// TODO Revisit our documentation
