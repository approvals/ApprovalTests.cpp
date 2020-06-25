#pragma once

#include <string>

namespace ApprovalTests
{
    class HelpMessages
    {
    public:
        static std::string getMisconfiguredBuildHelp(const std::string& fileName);

        static std::string getMisconfiguredMainHelp();

        static std::string topAndTailHelpMessage(const std::string& message);
    };
}
