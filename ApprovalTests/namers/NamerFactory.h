#pragma once

#include "ApprovalTestNamer.h"
#include "SectionNameDisposer.h"

#include <string>

namespace ApprovalTests
{
    struct NamerFactory
    {
        static SectionNameDisposer appendToOutputFilename(const std::string& sectionName)
        {
            return SectionNameDisposer(ApprovalTestNamer::currentTest(), sectionName);
        }
    };
}
