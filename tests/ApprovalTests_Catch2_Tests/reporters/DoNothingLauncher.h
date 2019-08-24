#ifndef APPROVALTESTS_CPP_DONOTHINGLAUNCHER_H
#define APPROVALTESTS_CPP_DONOTHINGLAUNCHER_H

#include "ApprovalTests/reporters/CommandLauncher.h"

#include <string>
#include <vector>
#include <numeric>

class DoNothingLauncher : public CommandLauncher
{
private:
    std::string cmd;
public:
    bool working = true;
    bool launch(std::vector<std::string> argv) override
    {
        for (std::vector<std::string>::iterator it = argv.begin();
            it != argv.end();
            ++it)
        {
            cmd += *it;
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
