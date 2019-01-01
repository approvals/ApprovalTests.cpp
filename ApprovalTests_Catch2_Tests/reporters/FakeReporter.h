#ifndef APPROVALTESTS_CPP_FAKEREPORTER_H
#define APPROVALTESTS_CPP_FAKEREPORTER_H

#include "../../ApprovalTests/reporters/Reporter.h"

class FakeReporter : public Reporter {
public:
    bool working;
    mutable bool called = false;

    FakeReporter(bool working = true) : working(working) {
    }

    virtual bool Report(std::string received, std::string approved) const
    {
        called = true;
        return working;
    }
};

#endif //APPROVALTESTS_CPP_FAKEREPORTER_H
