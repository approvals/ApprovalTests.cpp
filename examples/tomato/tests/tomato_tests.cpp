#include <igloo/igloo.h>
#include <approvals/Approvals.h>
#include <Tomato.h>

using namespace igloo;

Context( DescribeATomato )
{
    Spec( ItStartsInTheNewTomatoState )
    {
        PomodoroState *state = &PomodoroStates::New();
        LogManager lm;
        Tomato t( lm );
        Assert::That( &t.State(), Equals( state ) );
        Approvals::Verify( t.Menu() );
    }

    Spec( ItGoesToLoggingAfterNew )
    {
        PomodoroState *state = &PomodoroStates::Log();
        LogManager lm;
        Tomato t( lm );
        t.Next();
        Assert::That( &t.State(), Equals( state ) );
        Approvals::Verify( t.Menu() );
    }

    Spec( ItGoesToBreakAfterLogging )
    {
        PomodoroState *state = &PomodoroStates::BreakTime();
        LogManager lm;
        Tomato t( lm );
        t.Next();
        t.Next();
        Assert::That( &t.State(), Equals( state ) );
        Approvals::Verify( t.Menu() );
    }

    Spec( ItGoesBackToWorkAfterBreak )
    {
        PomodoroState *state = &PomodoroStates::ReturnToWork();
        LogManager lm;
        Tomato t( lm );
        t.Next();
        t.Next();
        t.Next( "1" );
        Assert::That( &t.State(), Equals( state ) );
        Approvals::Verify( t.Menu() );
    }

    Spec( ItGoesToLoggingAfterWork )
    {
        PomodoroState *state = &PomodoroStates::Log();
        LogManager lm;
        Tomato t( lm );
        t.Next();
        t.Next();
        t.Next( "1" );
        t.Next();
        Assert::That( &t.State(), Equals( state ) );
        Approvals::Verify( t.Menu() );
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