#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"

TEST_CASE("DisposableSample")
{
    // begin-snippet: disposable_correct
    auto disposer = ApprovalTests::Approvals::useApprovalsSubdirectory("directory");
    // end-snippet

    auto disposer2 =
        // begin-snippet: disposable_incorrect
        ApprovalTests::Approvals::useApprovalsSubdirectory("directory");
    // end-snippet
}
