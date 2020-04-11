#define BOOST_TEST_MODULE ModuleName

//#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test.hpp>

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

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

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    BOOST_CHECK(true);
    Approvals::verify("hello");
}

BOOST_AUTO_TEST_SUITE(NestedSuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    BOOST_CHECK(true);
    Approvals::verify("hello");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
