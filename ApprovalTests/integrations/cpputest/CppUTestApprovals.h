#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/Macros.h"

#ifdef APPROVALS_CPPUTEST_EXISTING_MAIN
#define APPROVALS_CPPUTEST
#endif

#ifdef APPROVALS_CPPUTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

// begin-snippet: required_headers_for_cpputest
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestPlugin.h>
#include <CppUTest/TestRegistry.h>
// end-snippet

namespace ApprovalTests
{
    class ApprovalTestsCppUTestPlugin : public TestPlugin
    {
    private:
        // We need to be able to delete currentTest at the end of the
        // test, to prevent CppUTest's leak-checking from triggering,
        // due to an undeleted std::string - so we use std::unique_ptr.
        std::unique_ptr<ApprovalTests::TestName> currentTest;

    public:
        ApprovalTestsCppUTestPlugin() : TestPlugin("ApprovalTestsCppUTestPlugin")
        {
            currentTest->sections.reserve(2);
        }

        APPROVAL_TESTS_NO_DISCARD static std::string
        cppUTestToString(const SimpleString& string)
        {
            return std::string{string.asCharString()};
        }

        void preTestAction(UtestShell& shell, TestResult& result) override
        {
            currentTest.reset(new ApprovalTests::TestName);
            currentTest->setFileName(cppUTestToString(shell.getFile()));

            currentTest->sections.emplace_back(cppUTestToString(shell.getGroup()));
            currentTest->sections.emplace_back(cppUTestToString(shell.getName()));

            ApprovalTests::ApprovalTestNamer::currentTest(currentTest.get());

            TestPlugin::preTestAction(shell, result);
        }

        void postTestAction(UtestShell& shell, TestResult& result) override
        {
            currentTest = nullptr;
            TestPlugin::postTestAction(shell, result);
        }
    };

    inline void initializeApprovalTestsForCppUTest()
    {
        static ApprovalTests::ApprovalTestsCppUTestPlugin logPlugin;
        TestRegistry::getCurrentRegistry()->installPlugin(&logPlugin);
    }
}

#ifndef APPROVALS_CPPUTEST_EXISTING_MAIN
int main(int argc, char** argv)
{
    ApprovalTests::initializeApprovalTestsForCppUTest();

    int result = CommandLineTestRunner::RunAllTests(argc, argv);
    TestRegistry::getCurrentRegistry()->resetPlugins();
    return result;
}
#endif

#endif // APPROVALS_CPPUTEST
