#ifndef APPROVALTESTS_CPP_COMMANDLAUNCHER_H
#define APPROVALTESTS_CPP_COMMANDLAUNCHER_H

#include <string>
#include <vector>

namespace ApprovalTests {
// An interface to trigger execution of a command. See also SystemLauncher
class CommandLauncher
{
public:
    virtual ~CommandLauncher() = default;
    virtual bool launch(std::vector<std::string> argv) = 0;
};
}

#endif  