#ifndef TOMATO_H
#define TOMATO_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "FileListener.h"
#include "LogManager.h"
#include "Menus.h"
#include "MessageCache.h"
#include "Timer.h"
#include "PomodoroState.h"

class Tomato
{
public:
    Tomato( LogManager &log );
    std::string Menu();
    void MoveTo( PomodoroState &nextState );
    Timer &Next( std::string response = "" );
    PomodoroState &State();
    Timer &GetTimer();
    Menus &GetMenus();
    void SetTimer( Timer t );
    void WriteLogEntry( std::string response );
private:
    PomodoroState *pomodoroState;
    Timer timer;
    Menus menu;
    LogManager *logger;
};
#endif