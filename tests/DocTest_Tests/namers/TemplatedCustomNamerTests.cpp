#include "doctest/doctest.h"
#include "ApprovalTests/namers/TemplatedCustomNamer.h"
#include "ApprovalTests/Approvals.h"

#include <iostream>

using namespace ApprovalTests;

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

TEST_CASE("Test non-unique name")
{
    Approvals::verifyExceptionMessage([]() { TemplatedCustomNamer("hello.txt"); });
}

TEST_CASE("Demo all namer templates")
{
    std::string fullText =
        "{RelativeTestSourceDirectory}/{ApprovalsSubdirectory}/"
        "{TestFileName}.{TestCaseName}.{ApprovedOrReceived}.{FileExtension}";

    std::string templateText = "Result: " + fullText + R"(

With breakdown:
RelativeTestSourceDirectory = {RelativeTestSourceDirectory}
ApprovalsSubdirectory       = {ApprovalsSubdirectory}
TestFileName                = {TestFileName}
TestCaseName                = {TestCaseName}
ApprovedOrReceived          = {ApprovedOrReceived}
FileExtension               = {FileExtension}

Also available:
TestSourceDirectory = {TestSourceDirectory}
)";
    TemplatedCustomNamer namer(templateText);
    std::regex pattern = std::regex(R"(TestSourceDirectory = .*DocTest_Tests/)",
                                    std::regex_constants::icase);
    Approvals::verify("For template: " + fullText + "\n\n" +
                          namer.getApprovedFileAsPath(".txt").toString("/"),
                      Options().withScrubber(Scrubbers::createRegexScrubber(
                          pattern,
                          "{TestSourceDirectory} = <full path to "
                          "sources>/ApprovalTests.cpp/tests/DocTest_Tests/")));
}

// ---- Docs
// TODO Document ApprovalTestNamer::setCheckBuildConfig(false)
// TODO Document the details and limitations of each template string
