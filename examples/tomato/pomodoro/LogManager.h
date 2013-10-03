#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Timer.h"
#include "LogListener.h"

class LogManager
{
private:
    std::vector<LogListener *> listeners;
public:
    void AddListener( LogListener &out );
    void Log( const Timer &t, const std::string &message );
};
#endif