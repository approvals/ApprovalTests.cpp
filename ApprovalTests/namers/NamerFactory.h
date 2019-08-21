#ifndef APPROVALTESTS_CPP_NAMERFACTORY_H
#define APPROVALTESTS_CPP_NAMERFACTORY_H

#include "ApprovalTestNamer.h"
#include "SectionNameDisposer.h"

#include <string>

struct NamerFactory
{
    static inline SectionNameDisposer appendToOutputFilename(std::string sectionName)
    {
        return SectionNameDisposer(ApprovalTestNamer::currentTest(), sectionName);
    }
};

#endif //APPROVALTESTS_CPP_NAMERFACTORY_H
