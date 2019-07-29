#ifndef APPROVALTESTS_CPP_DOCTESTAPPROVALS_H
#define APPROVALTESTS_CPP_DOCTESTAPPROVALS_H

#include "../ApprovalTests/namers/ApprovalTestNamer.h"

// <SingleHpp unalterable>
#ifdef APPROVALS_DOCTEST

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.hpp>

// anonymous namespace to prevent compiler -Wsubobject-linkage warnings
// This is OK as this code is only compiled on main()
namespace
{
    struct DocTestApprovalListener : doctest::ConsoleReporter
    {
        TestName currentTest;
    
        // constructor has to accept the ContextOptions by ref as a single argument
        DocTestApprovalListener(const doctest::ContextOptions& in) : ConsoleReporter(in)
        {
        }
    
        void test_case_start(const doctest::TestCaseData& testInfo) override
        {
            ConsoleReporter::test_case_start(testInfo);
    
            currentTest.sections.push_back(testInfo.m_name);
            currentTest.setFileName(testInfo.m_file);
            ApprovalTestNamer::currentTest(&currentTest);
        }
    
        void test_case_end(const doctest::CurrentTestCaseStats& in) override
        {
            ConsoleReporter::test_case_end(in);
    
            while (!currentTest.sections.empty()) {
                currentTest.sections.pop_back();
            }
        }
    
        void subcase_start(const doctest::SubcaseSignature &signature) override
        {
            ConsoleReporter::subcase_start(signature);
    
            currentTest.sections.push_back(signature.m_name);
        }
    
        void subcase_end() override
        {
            ConsoleReporter::subcase_end();
    
            currentTest.sections.pop_back();
        }
    };
}

REGISTER_REPORTER("approvals", 0, DocTestApprovalListener);

int main(int argc, char** argv)
{
    // See https://github.com/onqtam/doctest/blob/master/examples/all_features/main.cpp

    doctest::Context context(argc, argv);
    context.setOption("--reporters", "approvals");
    return context.run();
}

#endif // APPROVALS_DOCTEST
// </SingleHpp>
#endif //APPROVALTESTS_CPP_DOCTESTAPPROVALS_H
