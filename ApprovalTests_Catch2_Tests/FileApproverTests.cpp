#include "Catch.hpp"
#include "../ApprovalTests/StringWriter.h"
#include "reporters/TestReporter.h"
#include "../ApprovalTests/namers/ApprovalTestNamer.h"
#include "../ApprovalTests/FileApprover.h"
#include "../ApprovalTests/Approvals.h"

using namespace std;

TEST_CASE("ItVerifiesApprovedFileExists") {

    ApprovalTestNamer namer;
    StringWriter writer("Hello");
    TestReporter reporter;

    string approved = namer.getApprovedFile(".txt");
    string received = namer.getReceivedFile(".txt");

    string expected = "Failed Approval: \n"
                              "Approval File Not Found \n"
                              "File: \"" + approved+"\"";
    REQUIRE_THROWS_WITH(FileApprover::verify(namer, writer, reporter), expected);

    remove(approved.c_str());
    remove(received.c_str());
}


TEST_CASE("ItVerifiesExistingFiles") {
    ApprovalTestNamer namer;
    Approvals::verifyExistingFile(namer.getDirectory() + "sample.txt");
}


TEST_CASE("ItIgnoresLineEndingDifferences") {
    FileUtils::writeToFile("a.txt", "1\r\n2\n3\r\n4\r\n5");
    FileUtils::writeToFile("b.txt", "1\n2\r\n3\r\n4\n5");
    FileApprover::verify("a.txt", "b.txt");
}


TEST_CASE("ItComparesTheEntireFile") {
    FileUtils::writeToFile("a.txt", "12345");
    FileUtils::writeToFile("b.txt", "123");
    CHECK_THROWS_AS(FileApprover::verify("a.txt", "b.txt"), ApprovalMismatchException);
}

static bool LengthComparer(std::string receivedPath,
                           std::string approvedPath)
{
    return FileUtils::fileSize(receivedPath) == FileUtils::fileSize(approvedPath);
}

TEST_CASE("ItUsesCustomComparer") {
    FileUtils::writeToFile("a.length", "12345");
    FileUtils::writeToFile("b.length", "56789");
    FileApprover::registerComparer(".length", &LengthComparer);
    FileApprover::verify("a.length", "b.length");
}

