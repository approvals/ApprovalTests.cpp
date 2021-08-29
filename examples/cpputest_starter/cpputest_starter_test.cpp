#include "ApprovalTests.hpp"
#include "CppUTest/TestHarness.h"

TEST_GROUP(CppUTestStarter){};

TEST(CppUTestStarter, Sample)
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
