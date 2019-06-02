#ifndef APPROVALTESTS_CPP_AUTOAPPROVEREPORTER_H
#define APPROVALTESTS_CPP_AUTOAPPROVEREPORTER_H

#include "Reporter.h"
#include "../FileUtilsSystemSpecific.h"

class AutoApproveReporter : public Reporter
{
public:
    bool report(std::string received, std::string approved) const override
    {
        std::cout << "file " << approved << " automatically approved - next run should succeed\n";
        FileUtilsSystemSpecific::copyFile( received, approved );
        return true;
    }
};

#endif
