#ifndef COMMANDLAUNCHER_H
#define COMMANDLAUNCHER_H

#include <string>
#include <vector>

// An interface to trigger execution of a command. See also SystemLauncher
class CommandLauncher
{
public:
    virtual ~CommandLauncher() {}
    virtual bool launch(std::vector<std::string> argv) = 0;
};

#endif  