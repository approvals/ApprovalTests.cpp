#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#ifdef APPROVALS_BOOSTTEST
#define APPROVAL_TESTS_INCLUDE_CPPS

namespace ApprovalTests
{

    class BoostApprovalListener : public boost::unit_test::test_observer
    {
        ApprovalTests::TestName currentTest;

        void test_unit_start(boost::unit_test::test_unit const& test) override
        {
            std::string path(test.p_file_name.begin(), test.p_file_name.end());
            currentTest.setFileName(path);

            currentTest.sections.push_back(test.p_name);
            ApprovalTests::FrameworkIntegrations::setCurrentTest(&currentTest);
            ApprovalTests::FrameworkIntegrations::setTestPassedNotification(
                []() { BOOST_CHECK(true); });
        }

        void test_unit_finish(boost::unit_test::test_unit const& /*test*/,
                              unsigned long) override
        {
            currentTest.sections.pop_back();
        }
    };

    int register_our_listener(BoostApprovalListener& t)
    {
        boost::unit_test::framework::register_observer(t);
        return 1;
    }

    BoostApprovalListener o;
    auto dummy_variable = register_our_listener(o);
}

#endif // APPROVALS_BOOSTTEST
