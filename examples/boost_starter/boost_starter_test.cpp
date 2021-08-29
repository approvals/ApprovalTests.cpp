#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "ApprovalTests.hpp"

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    ApprovalTests::Approvals::verify(42);
}
BOOST_AUTO_TEST_SUITE_END()
