
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
        bool isForeground_ = false;

    public:
        explicit SystemLauncher(bool isForeground = false) : isForeground_(isForeground)
        {
        }

        bool launch(const std::string& commandLine) override
        {
            std::string launch = getCommandLine(commandLine);

            SystemUtils::runSystemCommandOrThrow(launch);
            return true;
        }

        // Seam for testing
        void invokeForWindows(bool useWindows)
        {
            useWindows_ = useWindows;
        }

        void setForeground(bool foreground)
        {
            isForeground_ = foreground;
        }

        bool isForeground() const
        {
            return isForeground_;
        }

        std::string getCommandLine(const std::string& commandLine) const override
        {
            std::string launch = useWindows_
                                     ? getWindowsCommandLine(commandLine, isForeground_)
                                     : getUnixCommandLine(commandLine, isForeground_);
            return launch;
        }

        std::string getWindowsCommandLine(const std::string& commandLine,
                                          bool foreground) const
        {
            std::string launch =
                foreground ? (std::string("cmd /S /C ") + "\"" + commandLine + "\"")
                           : ("start \"\" " + commandLine);

            return launch;
        }

        std::string getUnixCommandLine(const std::string& commandLine,
                                       bool foreground) const
        {
            std::string launch = foreground ? commandLine : (commandLine + " &");

            return launch;
        }
    };
}

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
