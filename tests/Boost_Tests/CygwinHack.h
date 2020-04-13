#ifdef __CYGWIN__
// Workaround for boost crash on cygwin: see #120

BOOST_AUTO_TEST_SUITE(SuiteName)
BOOST_AUTO_TEST_CASE(TestCaseName)
{
    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
#endif
