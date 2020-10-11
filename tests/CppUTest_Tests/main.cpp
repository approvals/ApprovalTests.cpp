// Get compiler error if these come after the CppUTest headers
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

#include <CppUTest/CommandLineTestRunner.h>
#include <CppUTest/TestPlugin.h>
#include <CppUTest/TestRegistry.h>

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

        std::string group{cppUTestToString(shell.getGroup())};
        currentTest.sections.emplace_back(group);

        std::string name{cppUTestToString(shell.getName())};
        currentTest.sections.emplace_back(name);

        ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);

        TestPlugin::preTestAction(shell, result);
    }

    void postTestAction(UtestShell& shell, TestResult& result) override
    {
        currentTest.sections.clear();
        TestPlugin::postTestAction(shell, result);
    }
};

int main(int ac, char** av)
{
    ApprovalTestsCppUTestPlugin logPlugin;
    TestRegistry::getCurrentRegistry()->installPlugin(&logPlugin);
    int result = CommandLineTestRunner::RunAllTests(ac, av);
    TestRegistry::getCurrentRegistry()->resetPlugins();
    return result;
}
