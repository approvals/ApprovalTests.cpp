#ifndef APPROVALTESTS_CPP_COMMANDREPORTER_H
#define APPROVALTESTS_CPP_COMMANDREPORTER_H

#include <utility>
#include "ApprovalTests/launchers/CommandLauncher.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/core/Reporter.h"

namespace ApprovalTests
{
    // Generic reporter to launch arbitrary command
    class CommandReporter : public Reporter
    {
    private:
        std::string cmd;
        CommandLauncher* l;

    protected:
        CommandReporter(std::string command, CommandLauncher* launcher)
            : cmd(std::move(command)), l(launcher)
        {
        }

    public:
        bool isTest = false;
        mutable std::string lastCommand;

        bool report(std::string received, std::string approved) const override
        {
            FileUtils::ensureFileExists(approved);
            if (isTest)
            {
                lastCommand =
                    l->getCommandLine(getFullCommand(received, approved));
                return true;
            }
            else
            {
                return l->launch(getFullCommand(received, approved));
            }
        }

        std::vector<std::string>
        getFullCommand(const std::string& received,
                       const std::string& approved) const
        {
            std::vector<std::string> fullCommand;
            fullCommand.push_back(cmd);
            fullCommand.push_back(received);
            fullCommand.push_back(approved);
            return fullCommand;
        }
    };
}
#endif //APPROVALTESTS_CPP_COMMANDREPORTER_H
