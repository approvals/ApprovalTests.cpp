#include "main.cpp"

//#define BOOST_TEST_INCLUDED
//#include <boost/test/unit_test.hpp>

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    Approvals::verify("hello");
}

BOOST_AUTO_TEST_SUITE(NestedSuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    Approvals::verify("hello");
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
