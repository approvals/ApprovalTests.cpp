#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/DateUtils.h"

using namespace ApprovalTests;

TEST_CASE("createDateTime")
{
    // begin-snippet: date_and_time
    std::chrono::system_clock::time_point dateTime =
        DateUtils::createUtcDateTime(2000, 1, 13, 3, 34, 45);

    std::string dateTimeString = DateUtils::toString(dateTime);
    // end-snippet
    Approvals::verify(dateTimeString);
}
