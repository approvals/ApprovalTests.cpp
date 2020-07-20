#pragma once

#include "ApprovalTests/launchers/CommandLauncher.h"

#include <string>
#include <numeric>

class DoNothingLauncher : public ApprovalTests::CommandLauncher
{
private:
    std::string cmd;

public:
    bool working = true;
    bool launch(const std::string& commandLine) override
    {
        cmd = commandLine;
        return working;
    }

    std::string receivedCommand()
    {
        return cmd;
    }

    std::string getCommandLine(const std::string& commandLine) const override
    {
        return commandLine;
    }
};
