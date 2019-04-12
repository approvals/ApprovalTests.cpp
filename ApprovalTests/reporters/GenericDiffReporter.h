#ifndef APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
#define APPROVALTESTS_CPP_GENERICDIFFREPORTER_H

#include "DiffPrograms.h"
#include "CommandReporter.h"
#include "SystemLauncher.h"
#include <string>
#include <vector>

class GenericDiffReporter : public CommandReporter {
private:
public:
    GenericDiffReporter(const std::string& program) : CommandReporter(program, getLauncher()) {};
    GenericDiffReporter(const DiffInfo& info) : CommandReporter(info.getProgramForOs().c_str(), getLauncher()) {};

    SystemLauncher* getLauncher()
    {
        // Leaks!
        /*
         * if SystemUtils::isCygwin()
         *  systemLauncher = new SystemLauncher(convertForCygwin);
         * else
         *  systemLauncher = new SystemLauncher;
         * return systemLauncher;
         * without leaking - e.g. std::unique_ptr
         */
        return new SystemLauncher(convertForCygwin);
    }

    static std::vector<std::string> convertForCygwin(std::vector<std::string> argv)
    {
        if (! SystemUtils::isCygwin())
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

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
