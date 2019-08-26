#include "Catch.hpp"
#include "ApprovalTests/StringWriter.h"
#include "reporters/TestReporter.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/FileApprover.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalException.h"
#include "Approvals.h"
#include "FileApprover.h"

TEST_CASE("ItVerifiesApprovedFileExists") {

    ApprovalTestNamer namer;
    StringWriter writer("Hello");
    TestReporter reporter;

    std::string approved = namer.getApprovedFile(".txt");
    std::string received = namer.getReceivedFile(".txt");

    std::string expected = "Failed Approval: \n"
                              "Approval File Not Found \n"
                              "File: \"" + approved+"\"";
    REQUIRE_THROWS_WITH(ApprovalTests::FileApprover::verify(namer, writer, reporter), expected);

    remove(approved.c_str());
    remove(received.c_str());
}


TEST_CASE("ItVerifiesExistingFiles") {
    ApprovalTestNamer namer;
    ApprovalTests::Approvals::verifyExistingFile(namer.getDirectory() + "../sample.txt");
}


TEST_CASE("ItIgnoresLineEndingDifferences") {
    FileUtils::writeToFile("a.txt", "1\r\n2\n3\r\n4\r\n5");
    FileUtils::writeToFile("b.txt", "1\n2\r\n3\r\n4\n5");
    ApprovalTests::FileApprover::verify("a.txt", "b.txt");
}


TEST_CASE("ItComparesTheEntireFile") {
    FileUtils::writeToFile("a.txt", "12345");
    FileUtils::writeToFile("b.txt", "123");
    CHECK_THROWS_AS(ApprovalTests::FileApprover::verify("a.txt", "b.txt"), ApprovalTests::ApprovalMismatchException);
}

// begin-snippet: create_custom_comparator
class LengthComparator : public ApprovalComparator
{
public:
    bool contentsAreEquivalent(std::string receivedPath, std::string approvedPath) const override
    {
        return FileUtils::fileSize(receivedPath) == FileUtils::fileSize(approvedPath);
    }
};
// end-snippet

TEST_CASE("ItUsesCustomComparator") {
    FileUtils::writeToFile("a.length", "12345");
    FileUtils::writeToFile("b.length", "56789");

    // begin-snippet: use_custom_comparator
    ApprovalTests::FileApprover::registerComparator(".length", std::make_shared<LengthComparator>());
    // end-snippet

    ApprovalTests::FileApprover::verify("a.length", "b.length");
}

