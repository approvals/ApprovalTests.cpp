
#ifndef APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
#define APPROVALTESTS_CPP_SYSTEMLAUNCHER_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "../SystemUtils.h"
#include "../FileUtils.h"
#include <vector>
#include <numeric>
#include "CommandLauncher.h"

class SystemLauncher : public CommandLauncher
{
public:
    bool exists(const std::string& command)
    {
        bool foundByWhich = false;
        if (!SystemUtils::isWindowsOs()) {
            std::string which = "which " + command + " > /dev/null 2>&1";
            int result = system(which.c_str());
            foundByWhich = (result == 0);
        }
        return  foundByWhich || FileUtils::fileExists(command);

    }

    bool launch(std::vector<std::string> argv) override
    {
        if (!exists(argv.front()))
        {
            return false;
        }

#if defined(__CYGWIN__)
        std::vector<std::string> copy = argv;
        for( size_t i = 0; i != argv.size(); ++i )
        {
            if ( i == 0)
            {
                copy[i] = "$(cygpath '"  + argv[i] + "')";
            }
            else
            {
                copy[i] = "$(cygpath -aw '"  + argv[i] + "')";
            }
        }
        argv = copy;
#endif

        std::string command = std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string a, std::string b) {return a + " " + "\"" + b + "\""; });
        std::string launch = SystemUtils::isWindowsOs() ? ("start \"\" " +  command) :  (command + " &");
        system(launch.c_str());
        return true;
    }
};

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
