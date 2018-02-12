#ifndef APPROVALS_H
#define APPROVALS_H

#include <string>
#include "FileApprover.h"
#include "reporters/DiffReporter.h"
#include "reporters/Reporter.h"
#include "namers/ApprovalNamer.h"

class Approvals
{
private:
    Approvals() {}
    ~Approvals() {}
public:
    static void verify( std::string contents,const Reporter& reporter = DiffReporter() )
    {
        StringWriter writer( contents );
        ApprovalNamer namer;
        FileApprover::verify(namer, writer, reporter);
    }

    template <typename T>
    static void verify(T contents, const Reporter& reporter = DiffReporter())
    {
        std::stringstream s;
        s << contents;
        verify(s.str(), reporter);
    }

};

#endif