#include <igloo/igloo.h>
#include <approvals/Approvals.h>
#include <Timer.h>

using namespace igloo;

Context( DescribeATimer )
{
    Spec( ItTellsYouWhenAnIntervalExpires )
    {
        Timer t( 10, 0 );
        Assert::That( t.IsExpired( 11 ), Equals( true ) );
    }

    Spec( ItTellsYouWhenTheIntervalHasNotExpired )
    {
        Timer t( 60, 0 );
        Assert::That( t.IsExpired( 30 ), Equals( false ) );
    }

    Spec( ItBeginsAtTheCurrentTimeByDefault )
    {
        Timer t( 10 );
        Assert::That( t.IsExpired( time( NULL ) + 10 ), Equals( true ) );
    }

    Spec( ItChecksTheCurrentTimeByDefault )
    {
        Timer t( 1 );
        sleep( 1 );
        Assert::That( t.IsExpired(), Equals( true ) );
    }

    Spec( ItCanTellYouTheStartTime )
    {
        Timer t( 10, 10 );
        Assert::That( t.Started(), Equals( 10 ) );
    }

    Spec( ItCanTellYouTheLastCheckedTime )
    {
        Timer t( 10, 0 );
        t.IsExpired( 38 );
        Assert::That( t.LastChecked(), Equals( 38 ) );
    }

    Spec( ItCanBeFormattedAsAString )
    {
        Timer t( 10, 0 );
        t.IsExpired( 1000 * 60 );
        Approvals::Verify( Timer::Format( t ) );
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