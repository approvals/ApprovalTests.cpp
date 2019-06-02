#ifndef APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H

#include "Reporter.h"
#include "AutoApproveReporter.h"
#include "../FileUtils.h"

class AutoApproveIfMissingReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        if (FileUtils::fileExists(approved))
        {
            return false;
        }

        return AutoApproveReporter().report(reporter, approved);
    }
};

#endif //APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
