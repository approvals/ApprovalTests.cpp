#ifndef APPROVALTESTS_CPP_SECTIONNAMEDISPOSER_H
#define APPROVALTESTS_CPP_SECTIONNAMEDISPOSER_H

#include "ApprovalTestNamer.h"

namespace ApprovalTests
{
    class APPROVAL_TESTS_NO_DISCARD SectionNameDisposer
    {
    public:
        SectionNameDisposer(TestName& currentTest, const std::string& scope_name)
            : currentTest(currentTest)
        {
            // Add extra section to output filename, to allow multiple files
            // to verified from a single test:
            currentTest.sections.push_back(scope_name);
        }

        ~SectionNameDisposer()
        {
            // Remove the extra section we added in the constructor
            currentTest.sections.pop_back();
        }

    private:
        TestName& currentTest;
    };
}

#endif //APPROVALTESTS_CPP_SECTIONNAMEDISPOSER_H
