#ifndef APPROVALTESTS_CPP_COMMANDLAUNCHER_H
#define APPROVALTESTS_CPP_COMMANDLAUNCHER_H

#include <string>
#include <vector>

namespace ApprovalTests
{
    // An interface to trigger execution of a command. See also SystemLauncher
    class CommandLauncher
    {
    public:
        virtual ~CommandLauncher() = default;
        virtual bool launch(const std::string& commandLine) = 0;
        virtual std::string getCommandLine(const std::string& commandLine) const = 0;
    };
}

#endif
