#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/FrameworkIntegrations.h"

#ifdef APPROVALS_UT
#define APPROVAL_TESTS_INCLUDE_CPPS

#if !(__GNUC__ >= 9 or __clang_major__ >= 9)
#error                                                                                   \
    "The [Boost].UT integration with Approval Tests requires source_location support by the compiler"
#endif

// begin-snippet: required_header_for_ut
#include <boost/ut.hpp>
// end-snippet

namespace ApprovalTests
{
    namespace cfg
    {
        void notify_success();

        class reporter : public boost::ut::reporter<boost::ut::printer>
        {
        private:
            TestName currentTest;

        public:
            auto on(boost::ut::events::test_begin test_begin) -> void
            {
                std::string name = std::string(test_begin.name);
                currentTest.sections.emplace_back(name);
                currentTest.setFileName(test_begin.location.file_name());

                ApprovalTests::FrameworkIntegrations::setCurrentTest(&currentTest);
                ApprovalTests::FrameworkIntegrations::setTestPassedNotification(
                    []() { notify_success(); });
                boost::ut::reporter<boost::ut::printer>::on(test_begin);
            }

            auto on(boost::ut::events::test_run test_run) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(test_run);
            }

            auto on(boost::ut::events::test_skip test_skip) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(test_skip);
            }

            auto on(boost::ut::events::test_end test_end) -> void
            {
                while (!currentTest.sections.empty())
                {
                    currentTest.sections.pop_back();
                }
                boost::ut::reporter<boost::ut::printer>::on(test_end);
            }

            template <class TMsg> auto on(boost::ut::events::log<TMsg> log) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(log);
            }

            template <class TExpr>
            auto on(boost::ut::events::assertion_pass<TExpr> location) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(location);
            }

            template <class TExpr>
            auto on(boost::ut::events::assertion_fail<TExpr> fail) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(fail);
            }

            auto on(boost::ut::events::fatal_assertion fatal) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(fatal);
            }

            auto on(boost::ut::events::exception exception) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(exception);
            }

            auto on(boost::ut::events::summary summary) -> void
            {
                boost::ut::reporter<boost::ut::printer>::on(summary);
            }
        };
    } // namespace cfg
}

template <>
auto boost::ut::cfg<boost::ut::override> =
    boost::ut::runner<ApprovalTests::cfg::reporter>{};

namespace ApprovalTests
{
    namespace cfg
    {
        void notify_success()
        {
            // This needs to be after the registering of our custom listener,
            // for compilation to succeed.
            boost::ut::expect(true);
        }
    }
}

#endif // APPROVALS_UT
