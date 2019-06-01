#ifndef APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H

#include "Reporter.h"
#include "../FileUtils.h"
#include "../FileUtilsSystemSpecific.h"

class AutoApproveIfMissingReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        if (FileUtils::fileExists(approved))
        {
            return false;
        }

        std::cout << "file " << approved << " automatically approved - next run should succeed\n";
        FileUtilsSystemSpecific::copyFile( received, approved );
        return true;
    }
};

#endif //APPROVALTESTS_CPP_AUTOAPPROVEIFMISSINGREPORTER_H
