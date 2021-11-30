
#pragma once

#include <string>
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/launchers/CommandLauncher.h"

namespace ApprovalTests
{
    class SystemLauncher : public CommandLauncher
    {
    private:
        bool useWindows_ = SystemUtils::isWindowsOs();
        bool isForeground_ = false;
        bool allowNonZeroExitCodes_ = false;

    public:
        explicit SystemLauncher(bool isForeground = false,
                                bool allowNonZeroExitCodes = false);

        bool launch(const std::string& commandLine) override;

        // Seam for testing
        void invokeForWindows(bool useWindows);

        void setForeground(bool foreground);

        void setAllowNonZeroExitCodes(bool allow);

        bool isForeground() const;

        std::string getCommandLine(const std::string& commandLine) const override;

        std::string getWindowsCommandLine(const std::string& commandLine,
                                          bool foreground) const;

        std::string getUnixCommandLine(const std::string& commandLine,
                                       bool foreground) const;
    };
}
