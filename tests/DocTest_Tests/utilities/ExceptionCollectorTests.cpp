#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/utilities/ExceptionCollector.h"

using namespace ApprovalTests;

TEST_CASE("ExceptionCollector")
{
    using namespace ApprovalTests;
    Approvals::verifyExceptionMessage([]() {
        ExceptionCollector exceptions;
        for (int i = 1; i <= 4; ++i)
        {
            exceptions.gather([&]() {
                throw std::runtime_error("error number " +
                                         StringUtils::toString(i));
            });
        }
        exceptions.release();
    });
}

TEST_CASE("ExceptionCollectorSampleTemplate")
{
    // begin-snippet: exception_collector_template
    ExceptionCollector exceptions;
    for (int i = 1; i <= 4; ++i)
    {
        exceptions.gather([&]() { /* Code that may throw errors here */ });
    }
    exceptions.release(); // All errors actually thrown together here
    // end-snippet
}
