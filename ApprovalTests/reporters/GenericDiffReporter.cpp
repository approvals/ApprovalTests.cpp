#include "ApprovalTests/reporters/GenericDiffReporter.h"

namespace ApprovalTests
{
    GenericDiffReporter::GenericDiffReporter(const std::string& program)
        : CommandReporter(program, &launcher)
    {
    }

    GenericDiffReporter::GenericDiffReporter(const DiffInfo& info)
        : CommandReporter(info.getProgramForOs(), info.arguments, &launcher)
    {
    }
}
