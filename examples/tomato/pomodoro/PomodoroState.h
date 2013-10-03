#ifndef POMODOROSTATE_H
#define POMODOROSTATE_H

#include <iostream>
#include <string>

class Tomato;

class PomodoroState
{
protected:
    PomodoroState() {};
public:
    virtual ~PomodoroState() {};
    virtual void HandleResponse( std::string response, Tomato *t ) = 0;
    virtual std::string MenuText( Tomato *t ) = 0;
    virtual void MoveNext( Tomato *t ) = 0;
    virtual void SetTimer( std::string response, Tomato *t ) = 0;
};

class BackToWork : public PomodoroState
{
public:
    std::string MenuText( Tomato *t );
    void MoveNext( Tomato *t );
    void SetTimer( std::string response, Tomato *t );
    void HandleResponse( std::string response, Tomato *t );
};

class Break : public PomodoroState
{
public:
    std::string MenuText( Tomato *t );
    void MoveNext( Tomato *t );
    void SetTimer( std::string response, Tomato *t );
    void HandleResponse( std::string response, Tomato *t );
};

class Logging : public PomodoroState
{
public:
    std::string MenuText( Tomato *t );
    void MoveNext( Tomato *t );
    void SetTimer( std::string response, Tomato *t );
    void HandleResponse( std::string response, Tomato *t );
};

class NewTomato : public PomodoroState
{
public:
    std::string MenuText( Tomato *t );
    void MoveNext( Tomato *t );
    void SetTimer( std::string response, Tomato *t );
    void HandleResponse( std::string response, Tomato *t );
};

class PomodoroStates
{
private:
    class StateInstances
    {
    private:
    public:
        PomodoroState *backToWork;
        PomodoroState *breakTime;
        PomodoroState *logging;
        PomodoroState *newTomato;

        StateInstances()
        {
            backToWork = new BackToWork();
            breakTime = new Break();
            logging = new Logging();
            newTomato = new NewTomato();
        }

        ~StateInstances()
        {
            delete backToWork;
            delete breakTime;
            delete logging;
            delete newTomato;
        }

    };

    static StateInstances states;

    PomodoroStates() {}
public:
    static PomodoroState &BreakTime();

    static PomodoroState &Log();

    static PomodoroState &New();

    static PomodoroState &ReturnToWork();
};

#endif