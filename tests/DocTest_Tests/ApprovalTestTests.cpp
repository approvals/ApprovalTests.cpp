#include "doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"

using namespace ApprovalTests;

TEST_CASE("YouCanUseAWriter")
{
    StringWriter writer("hello world", ".html");
    Approvals::verify(writer);
}
