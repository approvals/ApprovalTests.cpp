#pragma once

#include <string>
#include <vector>

namespace ApprovalTests
{
    class HelpMessages
    {
    public:
        static std::string getMisconfiguredBuildHelp(const std::string& fileName);

        static std::string getMisconfiguredMainHelp();

        static std::string getUnconfiguredRootDirectory();

        static std::string
        getUnknownEnvVarReporterHelp(const std::string& envVarName,
                                     const std::string& selected,
                                     const std::vector<std::string>& knowns);
        static std::string
        getInvalidEnvVarReporterHelp(const std::string& envVarName,
                                     const std::string& selected,
                                     const std::vector<std::string>& knowns);

        static std::string envVarErrorMessage(const std::string& envVarName,
                                              const std::string& selected,
                                              const std::vector<std::string>& knowns,
                                              std::string& helpMessage);

        static std::string topAndTailHelpMessage(const std::string& message);
    };
}
