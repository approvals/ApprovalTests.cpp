#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/Approvals.h"

#include <iostream>

using namespace ApprovalTests;

TEST_CASE("Test StringTemplates")
{
    // begin-snippet: templated_custom_namer_example
    TemplatedCustomNamer namer("/my/source/directory/{ApprovedOrReceived}/"
                               "{TestFileName}.{TestCaseName}.{FileExtension}");
    // end-snippet

    CHECK(namer.getApprovedFileAsPath(".txt").toString("/") ==
          "/my/source/directory/approved/"
          "TemplatedCustomNamerTests.Test_StringTemplates.txt");
    CHECK(namer.getReceivedFileAsPath(".txt").toString("/") ==
          "/my/source/directory/received/"
          "TemplatedCustomNamerTests.Test_StringTemplates.txt");
}

TEST_CASE("Test relative directory")
{
    TemplatedCustomNamer namer("{RelativeTestSourceDirectory}/{ApprovedOrReceived}/"
                               "{TestFileName}.{TestCaseName}.{FileExtension}");

    std::cout << "Root Directory: " << TestName::getRootDirectory() << '\n';
    std::cout << "__FILE__      : " << __FILE__ << '\n';
    CHECK(namer.getApprovedFileAsPath(".txt").toString("/") ==
          "namers/approved/"
          "TemplatedCustomNamerTests.Test_relative_directory.txt");
}

TEST_CASE("Test Namer Injection")
{
    // clang-format off
    // begin-snippet: templated_custom_namer_injection_via_options
    auto namer = TemplatedCustomNamer::create(
        "{TestSourceDirectory}/{ApprovalsSubdirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
    Approvals::verify("Hello", Options().withNamer(namer));
    // end-snippet

    // begin-snippet: templated_custom_namer_injection
    auto default_namer_disposer = TemplatedCustomNamer::useAsDefaultNamer(
        "{TestSourceDirectory}/{ApprovalsSubdirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
    // end-snippet
    // clang-format on

    Approvals::verify("Hello");
}

TEST_CASE("Test non-unique name")
{
    Approvals::verifyExceptionMessage([]() { TemplatedCustomNamer("hello.txt"); });
}

TEST_CASE("Demo all namer templates")
{
    std::string fullText =
        "{RelativeTestSourceDirectory}/{ApprovalsSubdirectory}/"
        "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";

    std::string templateText = "Everything = " + fullText + R"(

With breakdown:
RelativeTestSourceDirectory = {RelativeTestSourceDirectory}
ApprovalsSubdirectory = {ApprovalsSubdirectory}
TestFileName = {TestFileName}
TestCaseName = {TestCaseName}
ApprovedOrReceived = {ApprovedOrReceived}
FileExtension = {FileExtension}

Also available:
TestSourceDirectory = {TestSourceDirectory}
)";
    TemplatedCustomNamer namer(templateText);
    Approvals::verify(
        "For template: " + fullText + "\n\n" +
            namer.getApprovedFileAsPath(".txt").toString("/"),
        Options().withScrubber(Scrubbers::createRegexScrubber(
            R"(TestSourceDirectory = .*tests/)",
            "{TestSourceDirectory} = <full path to sources>ApprovalTests.cpp/tests/")));
}

// ---- Docs
// TODO Revisit our documentation
// TODO Document ApprovalTestNamer::setCheckBuildConfig(false)
// TODO Document the details and limitations of each template string

// TODO Document scenarios where this might be useful (when run outside of build dir, e.g. embedded)
// TODO Make documentation example use different filenames for approved and received, for safety
