#pragma once

#include "ApprovalTestNamer.h"
#include "ApprovalTests/utilities/Macros.h"

namespace ApprovalTests
{
    class APPROVAL_TESTS_NO_DISCARD SectionNameDisposer
    {
    public:
        SectionNameDisposer(TestName& currentTest_, const std::string& scope_name);
        SectionNameDisposer(const SectionNameDisposer&) = default;

        ~SectionNameDisposer();

    private:
        TestName& currentTest;
    };
}
