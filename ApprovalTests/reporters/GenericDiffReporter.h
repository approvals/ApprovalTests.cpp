#ifndef APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
#define APPROVALTESTS_CPP_GENERICDIFFREPORTER_H

#include "DiffPrograms.h"
#include "CommandReporter.h"
#include "SystemLauncher.h"
#include <string>
#include <vector>

namespace ApprovalTests {
class GenericDiffReporter : public CommandReporter {
private:
    SystemLauncher launcher;
public:
    GenericDiffReporter(const std::string& program) : CommandReporter(program, &launcher)
    {
        checkForCygwin();
    }
    GenericDiffReporter(const DiffInfo& info) : CommandReporter(info.getProgramForOs().c_str(), &launcher)
    {
        checkForCygwin();
    }

    void checkForCygwin()
    {
        if ( ApprovalTests::SystemUtils::isCygwin())
        {
            launcher.setConvertArgumentsForSystemLaunchingFunction(convertForCygwin);
        }
    }

    static std::vector<std::string> convertForCygwin(std::vector<std::string> argv)
    {
        if (! ApprovalTests::SystemUtils::isCygwin())
        {
            return argv;
        }
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
        return copy;
    }
};
}

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
