#ifndef DONOTHINGLAUNCHER_H
#define DONOTHINGLAUNCHER_H

#include "../../ApprovalTests/reporters/CommandLauncher.h"

#include <string>
#include <vector>
#include <numeric>

class DoNothingLauncher : public CommandLauncher
{
private:
    std::string cmd;
public:
    bool working = true;
    bool Launch(std::vector<std::string> argv)
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

    std::string ReceivedCommand()
    {
        return cmd;
    }
};

#endif  