#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "ApprovalTests.hpp"

using namespace ApprovalTests;

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    Approvals::verify(42);
}
BOOST_AUTO_TEST_SUITE_END()
