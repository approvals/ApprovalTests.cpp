#include "ApprovalTests/reporters/AutoApproveIfMissingReporter.h"

namespace ApprovalTests
{
    bool AutoApproveIfMissingReporter::report(std::string received,
                                              std::string approved) const
    {
        if (FileUtils::fileExists(approved))
        {
            return false;
        }

        return AutoApproveReporter().report(received, approved);
    }
}
