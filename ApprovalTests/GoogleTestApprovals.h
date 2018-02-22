#ifndef APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
#define APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H

#include "namers/ApprovalNamer.h"
#include "StringUtils.h"
#ifdef APPROVALS_GOOGLETEST

// <SingleHpp unalterable>
#include "gtest/gtest.h"


// Based on https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md
class MinimalistPrinter : public ::testing::EmptyTestEventListener
{
    TestName currentTest;
public:
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo& testInfo) override
    {
        currentTest.fileName = testInfo.file();
        // If the test case name equals the file name, skip the test case name
        if (StringUtils::contains(currentTest.fileName, std::string(testInfo.test_case_name()) + ".") )
        {
            currentTest.sections = { testInfo.name() };
        }
        else
        {
            currentTest.sections = { testInfo.test_case_name(), testInfo.name() };
        }
        
        ApprovalNamer::currentTest(&currentTest);
    }
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    // Gets hold of the event listener list.
    ::testing::TestEventListeners& listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new MinimalistPrinter);
    return RUN_ALL_TESTS();
}

// </SingleHpp>
#endif
#endif //APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
