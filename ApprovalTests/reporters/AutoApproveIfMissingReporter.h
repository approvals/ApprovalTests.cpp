#ifndef APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H

#include "ApprovalTests/core/Reporter.h"
#include "AutoApproveReporter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    class AutoApproveIfMissingReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override
        {
            if (FileUtils::fileExists(approved))
            {
                return false;
            }

            return AutoApproveReporter().report(received, approved);
        }
    };
}

#endif //APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
