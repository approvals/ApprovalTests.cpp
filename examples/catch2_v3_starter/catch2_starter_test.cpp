#include "catch2/catch_all.hpp"
#include "ApprovalTests.hpp"

TEST_CASE("catch2_starter sample")
{
    // TODO Replace 42 with the value or object whose contents you are verifying.
    // For help, see:
    // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
    ApprovalTests::Approvals::verify(42);
}
