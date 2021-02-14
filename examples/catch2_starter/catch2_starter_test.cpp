#include "catch2/catch.hpp"
#include "ApprovalTests.hpp"

using namespace ApprovalTests;

TEST_CASE("catch2_starter sample")
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    Approvals::verify(42);
}
