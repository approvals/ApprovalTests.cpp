#ifdef APPROVAL_TESTS_USE_CATCH2V3
#include <catch2/catch_test_macros.hpp>
#else
#include <catch2/catch.hpp>
#endif

void someFunction()
{
    CHECK(1 == 1);
}
