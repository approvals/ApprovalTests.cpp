#ifndef COMMANDLAUNCHER_H
#define COMMANDLAUNCHER_H

#include <string>
#include <vector>

class CommandLauncher
{
public:
    virtual ~CommandLauncher() {}
    virtual bool Launch(std::vector<std::string> argv) = 0;
};

#endif  