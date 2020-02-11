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

    };
}

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
