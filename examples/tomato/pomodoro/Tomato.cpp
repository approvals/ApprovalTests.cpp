#include "Tomato.h"

using namespace std;

Tomato::Tomato( LogManager &log )
    : pomodoroState( &PomodoroStates::New() ),
      timer( 0 ),
      logger( &log )
{
}

Timer &Tomato::Next( string response )
{
    State().HandleResponse( response, this );
    State().SetTimer( response, this );
    State().MoveNext( this );
    return GetTimer();
}

string Tomato::Menu()
{
    return State().MenuText( this );
}

PomodoroState &Tomato::State()
{
    return *pomodoroState;
}

void Tomato::MoveTo( PomodoroState &nextState )
{
    pomodoroState = &nextState;
}

Timer &Tomato::GetTimer()
{
    return timer;
}

void Tomato::SetTimer( Timer t )
{
    timer = t;
}

void Tomato::WriteLogEntry( string response )
{
    logger->Log( GetTimer(), response );
}

Menus &Tomato::GetMenus()
{
    return menu;
}