
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
    class SystemLauncher : public CommandLauncher
    {
    private:
        bool useWindows_ = SystemUtils::isWindowsOs();

    public:
        bool launch(std::vector<std::string> argv) override
        {
            std::string launch = getCommandLine(argv);

            SystemUtils::runSystemCommandOrThrow(launch);
            return true;
        }

        void invokeForWindows(bool useWindows)
        {
            useWindows_ = useWindows;
        }

        std::string getCommandLine(std::vector<std::string> argv) const override
        {
            std::string command =
                std::accumulate(argv.begin(),
                                argv.end(),
                                std::string(""),
                                [](const std::string& a, const std::string& b) {
                                    return a + " " + "\"" + b + "\"";
                                });
            std::string launch =
                useWindows_ ? ("start \"\" " + command) : (command + " &");
            return launch;
        }
    };
}

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
