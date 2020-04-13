#define BOOST_TEST_MODULE ModuleName

//#include <boost/test/unit_test.hpp> // static or dynamic boost build
#include <boost/test/included/unit_test.hpp> // header only boost

// begin-snippet: boost_test_main
// main.cpp (after #including boost.test)
#define APPROVALS_BOOSTTEST
#include "ApprovalTests.hpp"
// end-snippet
