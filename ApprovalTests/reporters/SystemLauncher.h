
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

typedef std::vector<std::string> (*ConvertArgumentsFunctionPointer)(std::vector<std::string>);

namespace ApprovalTests {
class SystemLauncher : public CommandLauncher
{
private:
    ConvertArgumentsFunctionPointer convertArgumentsForSystemLaunching;
public:
    SystemLauncher() : SystemLauncher(doNothing)
    {
    }

    explicit SystemLauncher(std::vector<std::string> (*pointer)(std::vector<std::string>)) : convertArgumentsForSystemLaunching(pointer) 
    {
    }

    // This function is an implementation detail for the support of Reporters on cygwin
    void setConvertArgumentsForSystemLaunchingFunction(ConvertArgumentsFunctionPointer function)
    {
        convertArgumentsForSystemLaunching = function;
    }

    bool exists(const std::string& command)
    {
        bool foundByWhich = false;
        if (!ApprovalTests::SystemUtils::isWindowsOs()) {
            std::string which = "which " + command + " > /dev/null 2>&1";
            int result = system(which.c_str());
            foundByWhich = (result == 0);
        }
        return  foundByWhich || ApprovalTests::FileUtils::fileExists(command);

    }

    static std::vector<std::string> doNothing(std::vector<std::string> argv)
    {
        return argv;
    }

    bool launch(std::vector<std::string> argv) override
    {
        if (!exists(argv.front()))
        {
            return false;
        }

        argv = convertArgumentsForSystemLaunching(argv);

        std::string command = std::accumulate(argv.begin(), argv.end(), std::string(""), [](std::string a, std::string b) {return a + " " + "\"" + b + "\""; });
        std::string launch = ApprovalTests::SystemUtils::isWindowsOs() ? ("start \"\" " + command) : (command + " &");
        system(launch.c_str());
        return true;
    }
};
}

#endif //APPROVALTESTS_CPP_SYSTEMLAUNCHER_H
