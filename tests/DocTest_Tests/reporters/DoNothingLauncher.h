#ifndef APPROVALTESTS_CPP_DONOTHINGLAUNCHER_H
#define APPROVALTESTS_CPP_DONOTHINGLAUNCHER_H

#include "ApprovalTests/launchers/CommandLauncher.h"

#include <string>
#include <vector>
#include <numeric>

class DoNothingLauncher : public ApprovalTests::CommandLauncher
{
private:
    std::string cmd;

public:
    bool working = true;
    bool launch(std::vector<std::string> argv) override
    {
        cmd = getCommandLine(argv);
        return working;
    }

    std::string receivedCommand()
    {
        return cmd;
    }

    std::string getCommandLine(std::vector<std::string> argv) const override
    {
        std::string result;
        for (auto& it : argv)
        {
            result += it;
            result += " ";
        }
        return result;
    }
};

#endif
