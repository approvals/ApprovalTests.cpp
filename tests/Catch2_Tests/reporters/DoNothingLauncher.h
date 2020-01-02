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
        for (auto& it : argv)
        {
            cmd += it;
            cmd += " ";
        }
        return working;
    }

    std::string receivedCommand()
    {
        return cmd;
    }
};

#endif
