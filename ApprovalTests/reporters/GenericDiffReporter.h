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
        }

        explicit GenericDiffReporter(const DiffInfo& info)
            : CommandReporter(info.getProgramForOs(), info.arguments, &launcher)
        {
        }
    };
}

#endif //APPROVALTESTS_CPP_GENERICDIFFREPORTER_H
