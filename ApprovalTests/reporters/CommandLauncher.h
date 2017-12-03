#ifndef COMMANDLAUNCHER_H
#define COMMANDLAUNCHER_H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <vector>

class CommandLauncher
{
public:
    virtual ~CommandLauncher() {}
    virtual void Launch( std::vector<std::string> argv ) = 0;
};

class DoNothingLauncher : public CommandLauncher
{
private:
    std::string cmd;
public:
    void Launch( std::vector<std::string> argv )
    {
        for ( std::vector<std::string>::iterator it = argv.begin();
                it != argv.end();
                ++it )
        {
            cmd += *it;
            cmd += " ";
        }
    }

    std::string ReceivedCommand()
    {
        return cmd;
    }
};

class SystemLauncher : public CommandLauncher
{
public:
    void Launch( std::vector<std::string> argv )
    {
        char *ARGV[argv.size() + 1];
        int count = 0;

        for ( std::vector<std::string>::iterator it = argv.begin();
                it != argv.end();
                ++it )
        {
            char *cstr = new char [it->length() + 1];
            std::strcpy( cstr, it->c_str() );
            ARGV[count] = cstr;
            count++;
        }

        ARGV[argv.size()] = NULL;

        if ( fork() == 0 )
        {
            int i = execvp( ARGV[0], ARGV );

            if ( i < 0 )
            {
                std::cerr << ARGV[0] << ": command not found" << std::endl;
                exit( 1 );
            }
        }

        for ( unsigned int i = 0; i < argv.size(); ++i )
        {
            delete ARGV[i];
        }
    }
};

#endif