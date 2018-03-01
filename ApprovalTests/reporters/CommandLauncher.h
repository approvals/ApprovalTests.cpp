#ifndef COMMANDLAUNCHER_H
#define COMMANDLAUNCHER_H

#include <string>
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

#endif  