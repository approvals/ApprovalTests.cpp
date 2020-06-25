#include "ApprovalTests/launchers/SystemLauncher.h"

namespace ApprovalTests
{
    SystemLauncher::SystemLauncher(bool isForeground) : isForeground_(isForeground)
    {
    }

    bool SystemLauncher::launch(const std::string& commandLine)
    {
        std::string launch = getCommandLine(commandLine);

        SystemUtils::runSystemCommandOrThrow(launch);
        return true;
    }

    void SystemLauncher::invokeForWindows(bool useWindows)
    {
        useWindows_ = useWindows;
    }

    void SystemLauncher::setForeground(bool foreground)
    {
        isForeground_ = foreground;
    }

    bool SystemLauncher::isForeground() const
    {
        return isForeground_;
    }

    std::string SystemLauncher::getCommandLine(const std::string& commandLine) const
    {
        std::string launch = useWindows_
                                 ? getWindowsCommandLine(commandLine, isForeground_)
                                 : getUnixCommandLine(commandLine, isForeground_);
        return launch;
    }

    std::string SystemLauncher::getWindowsCommandLine(const std::string& commandLine,
                                                      bool foreground) const
    {
        std::string launch = foreground
                                 ? (std::string("cmd /S /C ") + "\"" + commandLine + "\"")
                                 : ("start \"\" " + commandLine);

        return launch;
    }

    std::string SystemLauncher::getUnixCommandLine(const std::string& commandLine,
                                                   bool foreground) const
    {
        std::string launch = foreground ? commandLine : (commandLine + " &");

        return launch;
    }
}
