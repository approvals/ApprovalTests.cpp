#pragma once
 
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/utilities/Macros.h"

#ifdef APPROVALS_CPPUTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

// begin-snippet: required_header_for_cpputest
#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestPlugin.h>
#include <CppUTest/TestRegistry.h>
// end-snippet

namespace ApprovalTests
{
    class ApprovalTestsCppUTestPlugin : public TestPlugin
    {
    private:
        ApprovalTests::TestName currentTest;
    public:
        ApprovalTestsCppUTestPlugin() : TestPlugin("ApprovalTestsCppUTestPlugin")
        {
            // Turn off memory-leak-checking for now, as it generates errors which
            // I think are spurious.
            // The manual says:
            //      "It is common for the memory leak detection macros to conflict
            //      with an overloaded operator new or with STL."
            // http://cpputest.github.io/manual.html#memory_leak_detection
            //
            // I tried using the documented code to turn off leak-checking
            // by implementing setup() and teardown() - but got compiler errors - logged in
            // https://github.com/cpputest/cpputest/issues/1428
            MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
        }

        APPROVAL_TESTS_NO_DISCARD static std::string cppUTestToString(const SimpleString& string)
        {
            return std::string{string.asCharString()};
        }

        void preTestAction(UtestShell& shell, TestResult& result) override
        {
            currentTest.setFileName(cppUTestToString(shell.getFile()));

            currentTest.sections.emplace_back(cppUTestToString(shell.getGroup()));
            currentTest.sections.emplace_back(cppUTestToString(shell.getName()));

            ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);

            TestPlugin::preTestAction(shell, result);
        }

        void postTestAction(UtestShell& shell, TestResult& result) override
        {
            currentTest.sections.clear();
            TestPlugin::postTestAction(shell, result);
        }
    };
}

int main(int argc, char** argv)
{
    ApprovalTests::ApprovalTestsCppUTestPlugin logPlugin;
    TestRegistry::getCurrentRegistry()->installPlugin(&logPlugin);
    int result = CommandLineTestRunner::RunAllTests(argc, argv);
    TestRegistry::getCurrentRegistry()->resetPlugins();
    return result;
}

#endif // APPROVALS_CPPUTEST
