#ifndef __CYGWIN__
// Workaround for boost crash on cygwin: see #120

#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

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
#endif
