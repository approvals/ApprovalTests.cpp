#ifndef APPROVALS_H
#define APPROVALS_H

#include <string>
#include "FileApprover.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"

class Approvals
{
private:
    Approvals() {}
    ~Approvals() {}
public:
    static void verify( std::string contents )
    {
        StringWriter writer( contents );
        ApprovalNamer namer;
        MeldReporter reporter;
        FileApprover::verify(namer, writer, reporter);
    }
};

#endif