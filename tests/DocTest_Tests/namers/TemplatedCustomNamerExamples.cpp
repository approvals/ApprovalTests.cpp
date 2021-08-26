#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("Test StringTemplates")
{
    // begin-snippet: templated_custom_namer_example
    ApprovalTests::TemplatedCustomNamer namer(
        "/my/source/directory/{ApprovedOrReceived}/"
        "{TestFileName}.{TestCaseName}.{FileExtension}");
    // end-snippet

    CHECK(namer.getApprovedFileAsPath(".txt").toString("/") ==
          "/my/source/directory/approved/"
          "TemplatedCustomNamerExamples.Test_StringTemplates.txt");
    CHECK(namer.getReceivedFileAsPath(".txt").toString("/") ==
          "/my/source/directory/received/"
          "TemplatedCustomNamerExamples.Test_StringTemplates.txt");
}

TEST_CASE("Test Namer Injection")
{
    // clang-format off
    // begin-snippet: templated_custom_namer_injection_via_options
    auto namer = ApprovalTests::TemplatedCustomNamer::create(
        "{TestSourceDirectory}/{ApprovalsSubdirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
    ApprovalTests::Approvals::verify("Hello", ApprovalTests::Options().withNamer(namer));
    // end-snippet

    // begin-snippet: templated_custom_namer_injection
    auto default_namer_disposer = ApprovalTests::TemplatedCustomNamer::useAsDefaultNamer(
        "{TestSourceDirectory}/{ApprovalsSubdirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
    // end-snippet
    // clang-format on

    ApprovalTests::Approvals::verify("Hello");
}
