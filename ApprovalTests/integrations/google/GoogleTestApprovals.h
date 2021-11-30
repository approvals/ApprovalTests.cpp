#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/google/GoogleCustomizationsFactory.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"
#include "ApprovalTests/utilities/StringUtils.h"

#ifdef APPROVALS_GOOGLETEST_EXISTING_MAIN
#define APPROVALS_GOOGLETEST
#endif

#ifdef APPROVALS_GOOGLETEST
#define APPROVAL_TESTS_INCLUDE_CPPS

#include <gtest/gtest.h>

namespace ApprovalTests
{
    class GoogleTestListener : public testing::EmptyTestEventListener
    {
        TestName currentTest;

    public:
        bool isDuplicate(std::string testFileNameWithExtension, std::string testCaseName)
        {
            for (auto check : GoogleCustomizationsFactory::getEquivalencyChecks())
            {
                if (check(testFileNameWithExtension, testCaseName))
                {
                    return true;
                }
            }
            return false;
        }

        virtual void OnTestStart(const testing::TestInfo& testInfo) override
        {
            currentTest.setFileName(testInfo.file());
            currentTest.sections = {};
            if (!isDuplicate(currentTest.getFileName(), testInfo.test_case_name()))
            {
                currentTest.sections.emplace_back(testInfo.test_case_name());
            }
            if (!std::string(testInfo.name()).empty())
            {
                currentTest.sections.emplace_back(testInfo.name());
            }

            ApprovalTests::FrameworkIntegrations::setCurrentTest(&currentTest);
            ApprovalTests::FrameworkIntegrations::setTestPassedNotification(
                []() { EXPECT_TRUE(true); });
        }
    };

    inline void initializeApprovalTestsForGoogleTests()
    {
        auto& listeners = testing::UnitTest::GetInstance()->listeners();
        listeners.Append(new GoogleTestListener);
    }
}

#ifndef APPROVALS_GOOGLETEST_EXISTING_MAIN
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ApprovalTests::initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
#endif //APPROVALS_GOOGLETEST_EXISTING_MAIN

#endif
