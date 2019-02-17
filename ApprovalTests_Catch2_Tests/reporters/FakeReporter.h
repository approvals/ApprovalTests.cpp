#ifndef APPROVALTESTS_CPP_FAKEREPORTER_H
#define APPROVALTESTS_CPP_FAKEREPORTER_H

#include <ApprovalTests/reporters/Reporter.h>

class FakeReporter : public Reporter {
public:
    bool working;
    mutable bool called = false;

    FakeReporter(bool working = true) : working(working) {
    }

    virtual bool report(std::string received, std::string approved) const override
    {
        called = true;
        return working;
    }
};

#endif //APPROVALTESTS_CPP_FAKEREPORTER_H
