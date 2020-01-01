#ifndef APPROVALTESTS_CPP_NAMERFACTORY_H
#define APPROVALTESTS_CPP_NAMERFACTORY_H

#include "ApprovalTestNamer.h"
#include "SectionNameDisposer.h"

#include <string>

namespace ApprovalTests
{
    struct NamerFactory
    {
        static SectionNameDisposer
        appendToOutputFilename(const std::string& sectionName)
        {
            return SectionNameDisposer(ApprovalTestNamer::currentTest(),
                                       sectionName);
        }
    };
}

#endif //APPROVALTESTS_CPP_NAMERFACTORY_H
