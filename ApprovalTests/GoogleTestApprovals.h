#ifndef APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
#define APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H

#include "namers/ApprovalNamer.h"
#include "StringUtils.h"
#ifdef APPROVALS_GOOGLETEST

// <SingleHpp unalterable>
#include "gtest/gtest.h"


class GoogleTestListener : public ::testing::EmptyTestEventListener
{
    TestName currentTest;
public:
    virtual void OnTestStart(const ::testing::TestInfo& testInfo) override
    {
        currentTest.fileName = testInfo.file();
        currentTest.sections = {};
        if (! StringUtils::contains(currentTest.fileName, std::string(testInfo.test_case_name()) + ".") )
        {
            currentTest.sections.push_back(testInfo.test_case_name());
        }
        if (! std::string(testInfo.name()).empty())
        {
            currentTest.sections.push_back(testInfo.name());
        }
        
        ApprovalNamer::currentTest(&currentTest);
    }
};

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    auto& listeners = ::testing::UnitTest::GetInstance()->listeners();
    listeners.Append(new GoogleTestListener);
    return RUN_ALL_TESTS();
}

// </SingleHpp>
#endif
#endif //APPROVALTESTS_CPP_GOOGLTESTAPPPROVALS_H
