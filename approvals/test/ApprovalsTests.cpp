#include <igloo/igloo.h>
#include "../Approvals.h"
#include "../namers/IglooNamerFactory.h"
#include "../reporters/Reporter.h"
#include "../StringWriter.h"
#include "../FileApprover.h"

using namespace igloo;
using namespace std;

Context( DescribeTheVerifyMethod )
{
    Spec( ItVerifiesUsingConfiguredReporter )
    {
        stringstream expected;
        expected << "fake " <<
                 "/ApprovalsTests.DescribeTheVerifyMethod.ItVerifiesUsingConfiguredReporter.received.txt " <<
                 "/ApprovalsTests.DescribeTheVerifyMethod.ItVerifiesUsingConfiguredReporter.approved.txt ";
        TestReporter &reporter = ReporterFactory::UseReporter<TestReporter>();
        AssertThrows( ApprovalException, Approvals::Verify( "Hello" ) )
        string cmd = reporter.launcher.ReceivedCommand();
        string dir = IglooNamerFactory::TestDirectory();

        size_t at;

        do
        {
            at = cmd.find( dir );

            if ( at == string::npos )
            {
                break;
            }

            string b = cmd.substr( 0, at );
            string c = cmd.substr( at + dir.size() );
            cmd = b + c;
        }
        while ( at != string::npos );

        AssertThat( cmd, Equals( expected.str() ) );
        string received =
            IglooNamerFactory::GetCurrentNamer().GetReceivedFile( ".txt" );
        remove( received.c_str() );
    }
};

int main( int argc, char const *argv[] )
{
    DefaultTestResultsOutput output;
    TestRunner runner( output );

    IglooMetadataListener listener;
    runner.AddListener( &listener );
    MinimalProgressTestListener mpl;
    runner.AddListener( &mpl );

    return runner.Run();
}
