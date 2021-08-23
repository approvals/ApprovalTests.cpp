#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/DateUtils.h"

TEST_CASE("createDateTime")
{
    // begin-snippet: date_and_time
    std::chrono::system_clock::time_point dateTime =
        ApprovalTests::DateUtils::createUtcDateTime(2000, 1, 13, 3, 34, 45);

    std::string dateTimeString = ApprovalTests::DateUtils::toString(dateTime);
    // end-snippet
    ApprovalTests::Approvals::verify(dateTimeString);
}
