#ifndef APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
#define APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H

#include "Reporter.h"

namespace ApprovalTests {
namespace Detail {
//! Implementation detail of Approvals::useAsFrontLoadedReporter()
class DefaultFrontLoadedReporter : public Reporter
{
public:
    virtual bool report(std::string /*received*/, std::string /*approved*/) const override
    {
        return false;
    }
};
}
}

#endif //APPROVALTESTS_CPP_DEFAULTFRONTLOADEDREPORTER_H
