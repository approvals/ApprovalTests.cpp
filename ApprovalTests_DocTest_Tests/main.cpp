#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"

#include "../ApprovalTests/namers/ApprovalTestNamer.h"

using namespace doctest;

struct DocTestApprovalListener : ConsoleReporter
{
    TestName currentTest;

    // constructor has to accept the ContextOptions by ref as a single argument
    DocTestApprovalListener(const ContextOptions& in) : ConsoleReporter(in)
    {
    }
    
    void test_case_start(const TestCaseData& testInfo) override
    {
        ConsoleReporter::test_case_start(testInfo);

        currentTest.sections.push_back(testInfo.m_name);
        currentTest.setFileName(testInfo.m_file);
        ApprovalTestNamer::currentTest(&currentTest);
    }

    void test_case_end(const CurrentTestCaseStats& in) override
    {
        ConsoleReporter::test_case_end(in);
        
        while (!currentTest.sections.empty()) {
            currentTest.sections.pop_back();
        }
    }

    void subcase_start(const SubcaseSignature &signature) override
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

REGISTER_REPORTER("approvals", 0, DocTestApprovalListener);

int main(int argc, char** argv)
{
    const char *myargv[] = {"program name", "--reporters=approvals", NULL};
    int myargc = sizeof(myargv) / sizeof(char*) - 1;

    return doctest::Context(myargc, myargv).run();
}
