#ifndef APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H

#include "launchers/CommandLauncher.h"

namespace ApprovalTests
{
    // Based on SystemLauncher, and differs in that it runs the command in
    // the foreground instead of the background, so that any text output is
    // interleaved in with the output from the test framework.
    // This is an implementation detail of ConsoleDiffReporter, mainly.
    class ForegroundSystemLauncher : public CommandLauncher
    {
    public:
        bool launch(const std::string& commandLine) override
        {
            std::string launch = getCommandLine(commandLine);

            // Here we may be using textual diff tools to show the diffs between
            // two files that we already know are different.
            // And some diff-tools returns a non-zero status if the two files
            // are different.
            // So for this particular invoking of system(), it is fine if the
            // result is non-zero.
            // But we use the result, in order to suppress warnings from
            // static analysis tools.
            int exitCode = system(launch.c_str());
            APPROVAL_TESTS_UNUSED(exitCode);

            return true;
        }

        std::string
        getCommandLine(const std::string& commandLine) const override
        {
            // See https://stackoverflow.com/a/9965141/104370 for why the Windows string is so complex:
            const std::string launch =
                SystemUtils::isWindowsOs()
                    ? (std::string("cmd /S /C ") + "\"" + commandLine + "\"")
                    : (commandLine);
            return launch;
        }
    };
} // namespace ApprovalTests

#endif //APPROVALTESTS_CPP_FOREGROUNDSYSTEMLAUNCHER_H
