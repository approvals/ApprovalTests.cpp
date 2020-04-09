#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Sample

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Suite)

BOOST_AUTO_TEST_CASE(return_true)
{
    BOOST_CHECK(false);
}
BOOST_AUTO_TEST_SUITE_END()
