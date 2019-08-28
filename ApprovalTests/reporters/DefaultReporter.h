#ifndef APPROVALTESTS_CPP_DEFAULTREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTREPORTER_H

#include "Reporter.h"
#include "DefaultReporterFactory.h"

#include <string>

namespace ApprovalTests {
class DefaultReporter : public Reporter
{
public:
    virtual bool report(std::string received, std::string approved) const override
    {
        return DefaultReporterFactory::getDefaultReporter()->report(received, approved);
    }
};
}

#endif //APPROVALTESTS_CPP_DEFAULTREPORTER_H
