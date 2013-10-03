#include "PomodoroState.h"
#include "Tomato.h"

using namespace std;

PomodoroStates::StateInstances PomodoroStates::states;

PomodoroState &PomodoroStates::BreakTime()
{
    return *states.breakTime;
}

PomodoroState &PomodoroStates::Log()
{
    return *states.logging;
}

PomodoroState &PomodoroStates::New()
{
    return *states.newTomato;
}

PomodoroState &PomodoroStates::ReturnToWork()
{
    return *states.backToWork;
}

std::string NewTomato::MenuText( Tomato *t )
{
    return t->GetMenus().MainMenu();
}

void NewTomato::MoveNext( Tomato *t )
{
    t->MoveTo( PomodoroStates::Log() );
}

void NewTomato::SetTimer( std::string response, Tomato *t )
{
    t->SetTimer( Timer( 25 ) );
}

void NewTomato::HandleResponse( string response, Tomato *t )
{

}

std::string BackToWork::MenuText( Tomato *t )
{
    return t->GetMenus().BackToWorkMenu();
}

void BackToWork::MoveNext( Tomato *t )
{
    t->MoveTo( PomodoroStates::Log() );
}

void BackToWork::SetTimer( std::string response, Tomato *t )
{
    t->SetTimer( Timer( 25 ) );
}

void BackToWork::HandleResponse( string response, Tomato *t )
{

}

std::string Logging::MenuText( Tomato *t )
{
    return t->GetMenus().TomatoFinishedMenu();
}

void Logging::MoveNext( Tomato *t )
{
    t->MoveTo( PomodoroStates::BreakTime() );
}

void Logging::SetTimer( std::string response, Tomato *t )
{
    t->SetTimer( Timer( 0 ) );
}

void Logging::HandleResponse( string response, Tomato *t )
{
    t->WriteLogEntry( response );
}

std::string Break::MenuText( Tomato *t )
{
    return t->GetMenus().BreakMenu();
}

void Break::MoveNext( Tomato *t )
{
    t->MoveTo( PomodoroStates::ReturnToWork() );
}

void Break::SetTimer( std::string response, Tomato *t )
{
    int i = atoi( response.c_str() );
    int bt = 0;

    if ( i < 1 || 4 < i )
    {
        cout << "Don't understand. Try again." << endl;
    }
    else
    {
        switch ( i )
        {
        case 1:
            bt = 5;
            break;
        case 2:
            bt = 10;
            break;
        case 3:
            bt = 15;
            break;
        case 4:
            bt = 25;
            break;
        }
    }

    t->SetTimer( Timer( bt ) );
}

void Break::HandleResponse( string response, Tomato *t )
{

}
