
#include "ApprovalTests.hpp"
#include "Catch.hpp"

// See the tutorial at:
//   https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Tutorial.md#top



// begin-snippet: hello_approvals
TEST_CASE("HelloApprovals")
{
    Approvals::verify("Hello Approvals");
}
// end-snippet
