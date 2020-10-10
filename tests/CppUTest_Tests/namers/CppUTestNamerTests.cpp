#include "CppUTest/TestHarness.h"

TEST_GROUP(FirstTestGroup){};

TEST(FirstTestGroup, FirstTest)
{
    CHECK_EQUAL(1, 1);
}
