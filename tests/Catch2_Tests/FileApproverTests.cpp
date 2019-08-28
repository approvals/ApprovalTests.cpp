#include "Catch.hpp"
#include "ApprovalTests/writers/StringWriter.h"
#include "reporters/TestReporter.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/FileApprover.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("ItVerifiesApprovedFileExists") {

    ApprovalTests::ApprovalTestNamer namer;
    ApprovalTests::StringWriter writer("Hello");
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
    ApprovalTests::ApprovalTestNamer namer;
    ApprovalTests::Approvals::verifyExistingFile(namer.getDirectory() + "../sample.txt");
}


TEST_CASE("ItIgnoresLineEndingDifferences") {
    ApprovalTests::FileUtils::writeToFile("a.txt", "1\r\n2\n3\r\n4\r\n5");
    ApprovalTests::FileUtils::writeToFile("b.txt", "1\n2\r\n3\r\n4\n5");
    ApprovalTests::FileApprover::verify("a.txt", "b.txt");
}


TEST_CASE("ItComparesTheEntireFile") {
    ApprovalTests::FileUtils::writeToFile("a.txt", "12345");
    ApprovalTests::FileUtils::writeToFile("b.txt", "123");
    CHECK_THROWS_AS(ApprovalTests::FileApprover::verify("a.txt", "b.txt"), ApprovalTests::ApprovalMismatchException);
}

// begin-snippet: create_custom_comparator
class LengthComparator : public ApprovalTests::ApprovalComparator
{
public:
    bool contentsAreEquivalent(std::string receivedPath, std::string approvedPath) const override
    {
        return ApprovalTests::FileUtils::fileSize(receivedPath) == ApprovalTests::FileUtils::fileSize(approvedPath);
    }
};
// end-snippet

TEST_CASE("ItUsesCustomComparator") {
    ApprovalTests::FileUtils::writeToFile("a.length", "12345");
    ApprovalTests::FileUtils::writeToFile("b.length", "56789");

    // begin-snippet: use_custom_comparator
    ApprovalTests::FileApprover::registerComparator(".length", std::make_shared<LengthComparator>());
    // end-snippet

    ApprovalTests::FileApprover::verify("a.length", "b.length");
}

