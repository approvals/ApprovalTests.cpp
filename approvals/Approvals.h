#ifndef APPROVALS_H
#define APPROVALS_H

#include <string>
#include "FileApprover.h"
#include "StringWriter.h"
#include "namers/Namer.h"
#include "namers/IglooNamerFactory.h"
#include "reporters/Reporter.h"

class Approvals
{
private:
    Approvals() {}
    ~Approvals() {}
public:
    static void Verify( std::string contents )
    {
        StringWriter writer( contents );
        Namer &namer = IglooNamerFactory::GetCurrentNamer();
        Reporter &reporter = ReporterFactory::GetCurrentReporter();
        FileApprover::Verify( namer, writer, reporter );
    }
};

#endif