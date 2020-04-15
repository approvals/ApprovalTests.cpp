#pragma once

#include "ApprovalTests/reporters/GenericDiffReporter.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include "DoNothingLauncher.h"

class TestReporter : public ApprovalTests::CommandReporter
{
public:
    DoNothingLauncher launcher;

    TestReporter(bool working = true) : CommandReporter(getCommand(working), &launcher)
    {
        launcher.working = working;
        useCygwinConversions(false);
    };

    static std::string getKnownGoodCommand()
    {
        return ApprovalTests::SystemUtils::isWindowsOs()
                   ? R"(C:\Windows\System32\help.exe)"
                   : "echo";
    }

    static std::string getCommand(bool working)
    {
        return working ? getKnownGoodCommand() : "fake";
    }
};
