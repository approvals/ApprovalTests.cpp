#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/ExceptionCollector.h"
#include "ApprovalTests/utilities/StringUtils.h"

TEST_CASE("ExceptionCollector")
{
    using namespace ApprovalTests;
    Approvals::verifyExceptionMessage([]() {
        ExceptionCollector exceptions;
        for (int i = 1; i <= 4; ++i)
        {
            exceptions.gather([&]() {
                throw std::runtime_error("error number " + StringUtils::toString(i));
            });
        }
        exceptions.release();
    });
}

TEST_CASE("ExceptionCollectorSampleTemplate")
{
    // begin-snippet: exception_collector_template
    ApprovalTests::ExceptionCollector exceptions;

    for (int i = 1; i <= 4; ++i)
    {
        exceptions.gather([&]() { /* Code that may throw errors here */ });
    }
    exceptions.release(); // All errors actually thrown together here
    // end-snippet
}
