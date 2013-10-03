#ifndef LOGLISTENER_H
#define LOGLISTENER_H

#include <string>

class LogListener
{
protected:
    LogListener() {}
public:
    virtual ~LogListener() {}
    virtual void Insert( std::string message ) = 0;
};
#endif