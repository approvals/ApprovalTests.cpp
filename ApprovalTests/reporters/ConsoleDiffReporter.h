#ifndef APPROVALTESTS_CPP_CONSOLEDIFFREPORTER_H
#define APPROVALTESTS_CPP_CONSOLEDIFFREPORTER_H

#include "reporters/CommandReporter.h"
#include "reporters/DiffInfo.h"

#include "launchers/ForegroundSystemLauncher.h"

namespace ApprovalTests
{
    // Based on GenericDiffReporter, but using a different launcher, namely
    // ForegroundSystemLauncher so that the console output from the diff
    // tool is visible in CI logs.
    // Use TextDiffReporter if you just want reports of differences
    // to be sent to the console on any platform.
    class ConsoleDiffReporter : public CommandReporter
    {
    private:
        ApprovalTests::ForegroundSystemLauncher launcher;

    public:
        explicit ConsoleDiffReporter(const std::string& program)
            : CommandReporter(program, &launcher)
        {
        }

        explicit ConsoleDiffReporter(const DiffInfo& info)
            : CommandReporter(info.getProgramForOs(), &launcher)
        {
        }
    };
} // namespace ApprovalTests

#endif //APPROVALTESTS_CPP_CONSOLEDIFFREPORTER_H
