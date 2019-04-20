#ifndef APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
#define APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H

#include "namers/ApprovalTestNamer.h"
#include "StringUtils.h"

#ifdef APPROVALS_GOOGLETEST_EXISTING_MAIN
#define APPROVALS_GOOGLETEST
#endif

#ifdef APPROVALS_GOOGLETEST

// <SingleHpp unalterable>
#include "gtest/gtest.h"


class GoogleTestListener : public ::testing::EmptyTestEventListener
{
    TestName currentTest;
public:
    virtual void OnTestStart(const ::testing::TestInfo& testInfo) override
    {
        currentTest.setFileName(testInfo.file());
        currentTest.sections = {};
        if (! StringUtils::contains(currentTest.getFileName(), std::string(testInfo.test_case_name()) + ".") )
        {
            currentTest.sections.push_back(testInfo.test_case_name());
        }
        if (! std::string(testInfo.name()).empty())
        {
            currentTest.sections.push_back(testInfo.name());
        }
        
        ApprovalTestNamer::currentTest(&currentTest);
    }
};

void initializeApprovalTestsForGoogleTests() {
    auto& listeners = testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new GoogleTestListener);
}

#ifndef APPROVALS_GOOGLETEST_EXISTING_MAIN
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
#endif //APPROVALS_GOOGLETEST_EXISTING_MAIN

// </SingleHpp>
#endif
#endif //APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
