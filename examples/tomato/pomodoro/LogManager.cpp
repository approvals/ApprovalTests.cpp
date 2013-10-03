#include "LogManager.h"

using namespace std;

void LogManager::AddListener( LogListener &out )
{
    listeners.push_back( &out );
}

void LogManager::Log( const Timer &t, const string &message )
{
    stringstream full_message;
    full_message << Timer::Format( t ) << " " << message << endl;

    for ( std::vector<LogListener *>::iterator it = listeners.begin();
            it != listeners.end();
            ++it )
    {
        ( *it )->Insert( full_message.str() );
    }
}
