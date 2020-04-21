#include "doctest/doctest.h"
#include "ApprovalTests/core/ApprovalException.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

TEST_CASE("ApprovalMissingExceptionHasAMessage")
{
    ApprovalMissingException a("r.txt", "a.txt");
    std::string expected = "Failed Approval: \nApproval File Not Found \nFile: \"a.txt\"";
    REQUIRE(a.what() == expected);
}

TEST_CASE("ApprovalMismatchExceptionHasAMessage")
{
    ApprovalMismatchException a("r.txt", "a.txt");
    std::string expected = "Failed Approval: \n"
                           "Received does not match approved \n"
                           "Received : \"r.txt\" \n"
                           "Approved : \"a.txt\"";
    REQUIRE(a.what() == expected);
}

TEST_CASE("ApprovalMissingException is thrown")
{
    // Important to note that QuietReporter doesn't create the missing
    // approved file
    auto disposer =
        Approvals::useAsFrontLoadedReporter(std::make_shared<QuietReporter>());
    bool exception_caught = false;
    try
    {
        Approvals::verify("foo", Options(QuietReporter()));
    }
    catch (const ApprovalMissingException&)
    {
        exception_caught = true;
    }
    catch (const ApprovalException&)
    {
        exception_caught = false;
    }
    REQUIRE(exception_caught == true);
}
