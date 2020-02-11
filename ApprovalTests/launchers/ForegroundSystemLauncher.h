#ifndef APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H

#include "launchers/CommandLauncher.h"
#include "launchers/SystemLauncher.h"

namespace ApprovalTests
{
    // Based on SystemLauncher, and differs in that it runs the command in
    // the foreground instead of the background, so that any text output is
    // interleaved in with the output from the test framework.
    // This is an implementation detail of ConsoleDiffReporter, mainly.
    class ForegroundSystemLauncher : public CommandLauncher
    {
    public:
        bool launch(std::vector<std::string> argv) override
        {
            SystemLauncher temp_launcher;
            if (!temp_launcher.exists(argv.front()))
            {
                return false;
            }
            std::string launch = getCommandLine(argv);

            system(launch.c_str());
            return true;
        }

        std::string getCommandLine(std::vector<std::string> argv) const override
        {
            // Surround each of the arguments by double-quotes:
            const std::string command =
                std::accumulate(argv.begin(),
                                argv.end(),
                                std::string(""),
                                [](const std::string& a, const std::string& b) {
                                    return a + " " + "\"" + b + "\"";
                                });

            // See https://stackoverflow.com/a/9965141/104370 for why the Windows string is so complex:
            const std::string launch =
                SystemUtils::isWindowsOs()
                    ? (std::string("cmd /S /C ") + "\"" + command + "\"")
                    : (command);
            return launch;
        }
    };
} // namespace ApprovalTests

#endif //APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H
