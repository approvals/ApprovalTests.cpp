#include "ApprovalTests/namers/SectionNameDisposer.h"

namespace ApprovalTests
{
    SectionNameDisposer::SectionNameDisposer(TestName& currentTest_,
                                             const std::string& scope_name)
        : currentTest(currentTest_)
    {
        // Add extra section to output filename, to allow multiple files
        // to verified from a single test:
        currentTest_.sections.push_back(scope_name);
    }

    SectionNameDisposer::~SectionNameDisposer()
    {
        // Remove the extra section we added in the constructor
        currentTest.sections.pop_back();
    }
}
