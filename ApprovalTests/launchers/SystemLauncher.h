
#ifndef APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_SYSTEMLAUNCHER_H

#include <cstdlib>
#include <string>
#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include <vector>
#include <numeric>
#include "CommandLauncher.h"

namespace ApprovalTests
{
    using ConvertArgumentsFunctionPointer =
        std::vector<std::string> (*)(std::vector<std::string>);

    class SystemLauncher : public CommandLauncher
    {
    private:
        ConvertArgumentsFunctionPointer convertArgumentsForSystemLaunching;

    public:
        SystemLauncher() : SystemLauncher(doNothing)
        {
        }

        explicit SystemLauncher(
            std::vector<std::string> (*pointer)(std::vector<std::string>))
            : convertArgumentsForSystemLaunching(pointer)
        {
        }

        // This function is an implementation detail for the support of Reporters on cygwin
        void setConvertArgumentsForSystemLaunchingFunction(
            ConvertArgumentsFunctionPointer function)
        {
            convertArgumentsForSystemLaunching = function;
        }

        bool exists(const std::string& command)
        {
            bool foundByWhich = false;
            if (!SystemUtils::isWindowsOs())
            {
                std::string which = "which " + command + " > /dev/null 2>&1";
                int result = system(which.c_str());
                foundByWhich = (result == 0);
            }
            return foundByWhich || FileUtils::fileExists(command);
        }

        static std::vector<std::string> doNothing(std::vector<std::string> argv)
        {
            return argv;
        }

        bool launch(std::vector<std::string> argv) override
        {
            if (!exists(argv.front()) && (! SystemUtils::debugCommandLines().isTest))
            {
                return false;
            }

            argv = convertArgumentsForSystemLaunching(argv);

            std::string command =
                std::accumulate(argv.begin(),
                                argv.end(),
                                std::string(""),
                                [](const std::string& a, const std::string& b) {
                                    return a + " " + "\"" + b + "\"";
                                });
            std::string launch = SystemUtils::isWindowsOs()
                                     ? ("start \"\" " + command)
                                     : (command + " &");
            SystemUtils::runSystemCommandOrThrow(launch);
            return true;
        }
    };
}

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
