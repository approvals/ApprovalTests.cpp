// begin-snippet: boost_test_entry_point
#define BOOST_TEST_MODULE ModuleName
// end-snippet

//#include <boost/test/unit_test.hpp> // static or dynamic boost build
#include <boost/test/included/unit_test.hpp> // header only boost

// begin-snippet: boost_test_main
// test_entry_point.cpp file[s] (after #including boost.test)
#define APPROVALS_BOOSTTEST
#include "ApprovalTests.hpp"
// end-snippet
