#include "Timer.h"

using namespace std;


Timer::Timer( int seconds, time_t now ) : duration( seconds ), start( now )
{}

string Timer::Format( const Timer &t )
{
    string startedAt = FormatInstant( t.Started() );
    string endedAt = FormatInstant( t.LastChecked() );
    return startedAt + " - " + endedAt;
}

string Timer::FormatInstant( const time_t &i )
{
    struct tm *timeinfo = localtime( &i );

    char buffer[80];
    bzero( buffer, 80 );
    size_t count = strftime( buffer, 79, "%c", timeinfo );

    if ( count == 0 )
    {
        return "";
    }

    return string( buffer );
}

bool Timer::IsExpired( time_t now )
{
    lastCheck = now;
    return ( start + duration ) <= now;
}

time_t Timer::LastChecked() const
{
    return lastCheck;
}

time_t Timer::Started() const
{
    return start;
}