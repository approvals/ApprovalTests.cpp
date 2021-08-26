#include "doctest/doctest.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "../../DocTest_Tests/reporters/TestReporter.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/core/ApprovalException.h"
#include "ApprovalTests/core/FileApprover.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("ItVerifiesApprovedFileExists")
{

    ApprovalTestNamer namer;
    StringWriter writer("Hello");
    TestReporter reporter;

    std::string approved = namer.getApprovedFile(".txt");
    std::string received = namer.getReceivedFile(".txt");

    std::string expected = "Failed Approval: \n"
                           "Approval File Not Found \n"
                           "File: \"" +
                           approved + "\"";
    REQUIRE_THROWS_MESSAGE(FileApprover::verify(namer, writer, reporter), expected);

    remove(approved.c_str());
    remove(received.c_str());
}

TEST_CASE("ItVerifiesExistingFiles")
{
    ApprovalTestNamer namer;
    Approvals::verifyExistingFile(namer.getDirectory() + "../../sample.txt");
    Approvals::verifyExistingFile(namer.getDirectory() + "../../sample.txt", Options());
}

TEST_CASE("ItScrubsExistingFiles")
{
    ApprovalTestNamer namer;
    Approvals::verifyExistingFile(
        namer.getDirectory() + "../../sample.txt",
        Options(Scrubbers::createRegexScrubber("hired", "FIRED")));
}

TEST_CASE("ItIgnoresLineEndingDifferences")
{
    FileUtils::writeToFile("a.txt", "1\r\n2\n3\r\n4\r\n5");
    FileUtils::writeToFile("b.txt", "1\n2\r\n3\r\n4\n5");
    FileApprover::verify("a.txt", "b.txt");
}

TEST_CASE("ItComparesTheEntireFile")
{
    FileUtils::writeToFile("a.txt", "12345");
    FileUtils::writeToFile("b.txt", "123");
    CHECK_THROWS_AS(FileApprover::verify("a.txt", "b.txt"), ApprovalMismatchException);
}

namespace
{
    class IdenticalFilenamesNamer : public ApprovalNamer
    {
    public:
        APPROVAL_TESTS_NO_DISCARD
        std::string getApprovedFile(std::string extensionWithDot) const override
        {
            ApprovalTestNamer namer;
            return namer.getApprovedFile(extensionWithDot);
        }

        APPROVAL_TESTS_NO_DISCARD
        std::string getReceivedFile(std::string extensionWithDot) const override
        {
            // Intentionally return same name as approved:
            return getApprovedFile(extensionWithDot);
        }
    };
}

TEST_CASE("ItRejectsMatchingReceivedAndApprovedNames")
{
    auto default_namer_disposer = Approvals::useAsDefaultNamer(
        []() { return std::make_shared<IdenticalFilenamesNamer>(); });

    REQUIRE_THROWS_AS(
        Approvals::verify(
            "This should fail, as approved and verified filenames are identical"),
        std::runtime_error);
}
