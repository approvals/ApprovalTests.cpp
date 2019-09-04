#include "doctest.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("DisposableSample")
{
    using namespace ApprovalTests;
    // begin-snippet: disposable_correct
    auto disposer = Approvals::useApprovalsSubdirectory("directory");
    // end-snippet

    auto disposer2 =
    // begin-snippet: disposable_incorrect
    Approvals::useApprovalsSubdirectory("directory");
    // end-snippet
}
