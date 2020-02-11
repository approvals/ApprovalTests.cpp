
#ifndef APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_SYSTEMLAUNCHER_H

#include <cstdlib>
#include <string>
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include <vector>
#include "CommandLauncher.h"

namespace ApprovalTests
{
    class SystemLauncher : public CommandLauncher
    {
    private:
        bool useWindows_ = SystemUtils::isWindowsOs();

    public:
        bool launch(const std::string& commandLine) override
        {
            std::string launch = getCommandLine(commandLine);

            SystemUtils::runSystemCommandOrThrow(launch);
            return true;
        }

        void invokeForWindows(bool useWindows)
        {
            useWindows_ = useWindows;
        }

        std::string
        getCommandLine(const std::string& commandLine) const override
        {
            std::string launch = useWindows_ ? ("start \"\" " + commandLine)
                                             : (commandLine + " &");
            return launch;
        }
    };
}

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
