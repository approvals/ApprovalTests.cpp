#ifndef APPROVALTESTS_CPP_COMMANDLAUNCHER_H
#define APPROVALTESTS_CPP_COMMANDLAUNCHER_H

#include <string>
#include <vector>

namespace ApprovalTests
{
    using ConvertArgumentsFunctionPointer =
        std::vector<std::string> (*)(std::vector<std::string>);

    // An interface to trigger execution of a command. See also SystemLauncher
    class CommandLauncher
    {
    public:
        virtual ~CommandLauncher() = default;
        virtual bool launch(std::vector<std::string> argv) = 0;
        virtual std::string
        getCommandLine(std::vector<std::string> argv) const = 0;
        virtual void setConvertArgumentsForSystemLaunchingFunction(
            ConvertArgumentsFunctionPointer function) = 0;
    };
}

#endif
