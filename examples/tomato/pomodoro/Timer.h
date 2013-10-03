#ifndef TIMER_H
#define TIMER_H

#include <cstring>
#include <ctime>
#include <string>

class Timer
{
private:
    int duration;
    time_t lastCheck;
    time_t start;

public:
    Timer( int seconds, time_t now = time( NULL ) );

    static std::string Format( const Timer &t );
    static std::string FormatInstant( const time_t &i );
    bool IsExpired( time_t now = time( NULL ) );
    time_t LastChecked() const;
    time_t Started() const;
};
#endif