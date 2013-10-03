#include <igloo/igloo.h>
#include <approvals/Approvals.h>
#include <LogManager.h>
#include <Timer.h>
#include <string>
#include <sstream>
#include <MessageCache.h>

using namespace igloo;
using namespace std;

Context( DescribeALogManager )
{
    Spec( ItWritesMessages )
    {
        MessageCache mc( 1 );
        Timer t( 10, 0 );
        t.IsExpired( 25 * 60 );

        LogManager l;
        l.AddListener( mc );
        l.Log( t, "Hello World" );
        Approvals::Verify( mc.Messages() );
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