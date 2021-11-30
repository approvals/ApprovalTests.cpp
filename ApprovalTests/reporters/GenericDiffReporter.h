#pragma once

#include "ApprovalTests/reporters/DiffPrograms.h"
#include "ApprovalTests/reporters/CommandReporter.h"
#include "ApprovalTests/launchers/SystemLauncher.h"
#include <string>

namespace ApprovalTests
{
    class GenericDiffReporter : public CommandReporter
    {
    public:
        SystemLauncher launcher;

    public:
        explicit GenericDiffReporter(const std::string& program);

        explicit GenericDiffReporter(const DiffInfo& info);
    };
}
