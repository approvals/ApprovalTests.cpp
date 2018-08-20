#include "Catch.hpp"
#include "../ApprovalTests/StringWriter.h"
#include "../ApprovalTests/reporters/GenericDiffReporter.h"
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
	FileUtils::writeToFile("a.txt", "1\r\n2\n3\r\n4");
	FileUtils::writeToFile("b.txt", "1\n2\r\n3\r\n4");
	REQUIRE( FileApprover::verify("a.txt", "b.txt") == NULL);
}
