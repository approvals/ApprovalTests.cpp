#ifndef APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H
#define APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/CheckFileMacroIsAbsolute.h"

#ifdef APPROVALS_BOOSTTEST

namespace ApprovalTests
{

    class Observer : public boost::unit_test::test_observer
    {
        ApprovalTests::TestName currentTest;

        void test_unit_start(boost::unit_test::test_unit const& test) override
        {
            std::string path(test.p_file_name.begin(), test.p_file_name.end());
            currentTest.setFileName(path);

            currentTest.sections.push_back(test.p_name);
            ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
        }

        void test_unit_finish(boost::unit_test::test_unit const& test,
                              unsigned long) override
        {
            currentTest.sections.pop_back();
        }
    };

    int register_our_observer(Observer& t)
    {
        boost::unit_test::framework::register_observer(t);
        return 1;
    }

    Observer o;
    auto dummy_variable = register_our_observer(o);
}

#endif // APPROVALS_BOOSTTEST
#endif //APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H