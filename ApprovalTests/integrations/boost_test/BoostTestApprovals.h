#ifndef APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H
#define APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/CheckFileMacroIsAbsolute.h"

//#if defined(APPROVALS_BOOSTTEST_EXISTING_MAIN)
//#define APPROVALS_BOOSTTEST
//#define BOOSTTEST_CONFIG_IMPLEMENT
//#elif defined(APPROVALS_BOOSTTEST)
//#define BOOSTTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#endif

#ifdef APPROVALS_BOOSTTEST

//// begin-snippet: required_header_for_doctest
//#include <doctest/doctest.h>
//// end-snippet

//namespace ApprovalTests
//{

    class Observer : public boost::unit_test::test_observer
    {
        ApprovalTests::TestName currentTest;
        void test_unit_start(boost::unit_test::test_unit const& test) override
        {
            std::cout << "hello " << test.p_file_name << " " << test.p_name << " "
                      << test.p_type_name << " " << test.p_description << " "
                      << test.full_name() << std::endl;

            std::string path(test.p_file_name.begin(), test.p_file_name.end());
            currentTest.setFileName(path);

            currentTest.sections.push_back(test.p_name);
            ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
        }
        void test_unit_finish(boost::unit_test::test_unit const& test, unsigned long) override
        {
            std::cout << "Exiting " << test.p_name << '\n';
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
//}


#endif // APPROVALS_BOOSTTEST
#endif //APPROVALTESTS_CPP_BOOSTTESTAPPROVALS_H
