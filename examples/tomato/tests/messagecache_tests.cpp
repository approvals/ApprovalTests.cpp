#include <igloo/igloo.h>
#include <approvals/Approvals.h>
#include <MessageCache.h>
#include <string>

using namespace igloo;
using namespace std;

Context( DescribeAMessageCache )
{
    Spec( YouCanWriteMessagesToIt )
    {
        MessageCache c( 1 );
        c.Insert( "Hello World" );
        Approvals::Verify( c.Messages() );
    }

    Spec( TheNumberOfMessagesIsLimited )
    {
        MessageCache c( 5 );

        for ( int i = 0; i < 10; ++i )
        {
            string s;
            s.push_back( char( i + 33 ) );
            c.Insert( s );
        }

        Approvals::Verify( c.Messages() );
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