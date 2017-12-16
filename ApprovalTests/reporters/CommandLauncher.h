#ifndef COMMANDLAUNCHER_H
#define COMMANDLAUNCHER_H

#include <cstring>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "../SystemUtils.h"
#include <vector>
#include <numeric>

class CommandLauncher
{
public:
    virtual ~CommandLauncher() {}
    virtual bool Launch(std::vector<std::string> argv) = 0;
};

class DoNothingLauncher : public CommandLauncher
{
private:
    std::string cmd;
public:
    bool working = true;
    bool Launch(std::vector<std::string> argv)
    {
        for (std::vector<std::string>::iterator it = argv.begin();
            it != argv.end();
            ++it)
        {
            cmd += *it;
            cmd += " ";
        }
        return working;
    }

    std::string ReceivedCommand()
    {
        return cmd;
    }
};

class SystemLauncher : public CommandLauncher
{
public:
    bool exists(const std::string& command)
    {
        bool foundByWhich = false;
        if (!SystemUtils::isWindowsOs()) {
            std::string which = "which " + command + " > /dev/null 2>&1";
            int result = system(which.c_str());
            foundByWhich = (result == 0);
        }
        return  foundByWhich || FileUtils::fileExists(command);

    }

    bool Launch(std::vector<std::string> argv)
    {
        if (!exists(argv.front()))
        {
            return false;
        }

        std::string command =   std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string a, std::string b) {return a +" " + b; } );
        std::string launch = SystemUtils::isWindowsOs() ? ("start " +  command) :  (command + " &");
        system(command.c_str());
        return true;
}
};

#endif  