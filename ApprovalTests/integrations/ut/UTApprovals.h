#ifndef APPROVALTESTS_CPP_UTAPPROVALS_H
#define APPROVALTESTS_CPP_UTAPPROVALS_H

#include "ApprovalTests/namers/ApprovalTestNamer.h"

// <SingleHpp unalterable>
#ifdef APPROVALS_UT

#include <ut.hpp>

namespace ApprovalTests
{
    namespace cfg {
        class reporter : public boost::ut::reporter<boost::ut::printer> {
            private:
                TestName currentTest;

            public:
                auto on(boost::ut::events::test_begin test_begin) -> void {
                    std::string name = test_begin.name;
                    currentTest.sections.emplace_back(name);

                    const std::string fileName = 
                        boost::ut::reflection::source_location::current().file_name();
                    currentTest.setFileName(fileName);

                    ApprovalTestNamer::currentTest(&currentTest);

                    boost::ut::reporter<boost::ut::printer>::on(test_begin);
                }

                auto on(boost::ut::events::test_run test_run) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(test_run);
                }

                auto on(boost::ut::events::test_skip test_skip) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(test_skip);
                }

                auto on(boost::ut::events::test_end test_end) -> void {
                    while (!currentTest.sections.empty()) {
                        currentTest.sections.pop_back();
                    }
                    boost::ut::reporter<boost::ut::printer>::on(test_end);
                }

                template <class TMsg>
                auto on(boost::ut::events::log<TMsg>) -> void {}

                template <class TLocation, class TExpr>
                auto on(boost::ut::events::assertion_pass<TLocation, TExpr> location) -> void {
                    boost::ut::reporter<boost::ut::printer>::on(location);
                }

                template <class TLocation, class TExpr>
                auto on(boost::ut::events::assertion_fail<TLocation, TExpr> fail) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(fail);
                }

                auto on(boost::ut::events::fatal_assertion fatal) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(fatal);
                }

                auto on(boost::ut::events::exception exception) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(exception);
                }

                auto on(boost::ut::events::summary summary) -> void { 
                    boost::ut::reporter<boost::ut::printer>::on(summary);
                }
        };
    }  // namespace cfg
}

template <>
auto boost::ut::cfg<boost::ut::override> = boost::ut::runner<ApprovalTests::cfg::reporter>{};

#endif // APPROVALS_UT
// </SingleHpp>
#endif //APPROVALTESTS_CPP_UTAPPROVALS_H
