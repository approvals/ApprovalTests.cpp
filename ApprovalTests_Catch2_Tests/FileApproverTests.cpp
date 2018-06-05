#include "Catch.hpp"
#include "../ApprovalTests/StringWriter.h"
#include "../ApprovalTests/reporters/GenericDiffReporter.h"
#include "../ApprovalTests/namers/ApprovalTestNamer.h"
#include "../ApprovalTests/FileApprover.h"

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


/*
    Spec( ItLaunchesReporterOnFailure )
    {
        Namer namer( bin(),
                     "DescribeAFileApprover.ItLaunchesReporterOnFailure" );
        string approved = namer.GetApprovedFile( ".txt" );
        string received = namer.GetReceivedFile( ".txt" );
        writeMessageTo( "olleH", approved );
        StringWriter writer( "Hello" );
        TestReporter reporter;

        string expected = "fake " + received + " " + approved + " ";
        AssertThrows( ApprovalException,
                      FileApprover::Verify( namer, writer, reporter ) );
        AssertThat( reporter.launcher.ReceivedCommand(),
                    Equals( expected ) );

        remove( approved.c_str() );
        remove( received.c_str() );
    }

};
 */

