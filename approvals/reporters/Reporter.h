#ifndef REPORTER_H
#define REPORTER_H

#include "CommandLauncher.h"

class Reporter
{
private:
    std::string cmd;
    CommandLauncher *l;

protected:
    Reporter( std::string command, CommandLauncher *launcher )
        : cmd( command ), l( launcher )
    {
    }

public:
    void Report( std::string received, std::string approved )
    {
        std::vector<std::string> fullCommand;
        fullCommand.push_back( cmd );
        fullCommand.push_back( received );
        fullCommand.push_back( approved );
        l->Launch( fullCommand );
    }
};

class MeldReporter : public Reporter
{
private:
    SystemLauncher launcher;

public:
    MeldReporter() : Reporter( "meld", &launcher ) {};
};

class TestReporter : public Reporter
{
public:
    DoNothingLauncher launcher;
    TestReporter() : Reporter( "fake", &launcher ) {};
};

class ReporterFactory
{
private:
    static Reporter *reporter;
    ReporterFactory()  {}
    ~ReporterFactory() {}
public:
    static Reporter &GetCurrentReporter()
    {
        return *reporter;
    }

    template<typename ReporterType>
    static ReporterType &UseReporter()
    {
        if ( reporter != NULL )
        {
            delete reporter;
        }

        ReporterType *t = new ReporterType();
        reporter = t;
        return *t;
    }
};

Reporter *ReporterFactory::reporter = new MeldReporter();

#endif