#ifndef APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
#define APPROVALTESTS_CPP_GENERICDIFFREPORTER_H

#include "DiffPrograms.h"
#include "CommandReporter.h"
#include "ApprovalTests/launchers/SystemLauncher.h"
#include <string>
#include <vector>

namespace ApprovalTests
{
    class GenericDiffReporter : public CommandReporter
    {
    public:
        SystemLauncher launcher;

    public:
        explicit GenericDiffReporter(const std::string& program)
            : CommandReporter(program, &launcher)
        {
            checkForCygwin();
        }
        explicit GenericDiffReporter(const DiffInfo& info)
            : CommandReporter(info.getProgramForOs(), &launcher)
        {
            checkForCygwin();
        }

        void checkForCygwin()
        {
            useCygwinConversions(SystemUtils::isCygwin());
        }

        void useCygwinConversions(bool useCygwin)
        {
            if (useCygwin)
            {
                launcher.setConvertArgumentsForSystemLaunchingFunction(
                    convertForCygwin);
            }
            else
            {
                launcher.setConvertArgumentsForSystemLaunchingFunction(
                    SystemLauncher::doNothing);
            }
        }

        static std::vector<std::string>
        convertForCygwin(std::vector<std::string> argv)
        {
            std::vector<std::string> copy = argv;
            for (size_t i = 0; i != argv.size(); ++i)
            {
                if (i == 0)
                {
                    const std::string& arg_value = argv[i];
                    copy[i] = convertProgramForCygwin(arg_value);
                }
                else
                {
                    const std::string& arg_value = argv[i];
                    copy[i] = convertFileArgumentForCygwin(arg_value);
                }
            }
            return copy;
        }

        static std::string convertProgramForCygwin(const std::string& arg_value)
        {
            return "$(cygpath '" + arg_value + "')";
        }

        static std::string convertFileArgumentForCygwin(const std::string& arg_value)
        {
            return "$(cygpath -aw '" + arg_value + "')";
        }
    };
}

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
