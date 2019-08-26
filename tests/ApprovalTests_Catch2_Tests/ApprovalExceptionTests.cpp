#include "Catch.hpp"
#include "ApprovalTests/ApprovalException.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/QuietReporter.h"

TEST_CASE("ApprovalMissingExceptionHasAMessage") {
    ApprovalTests::ApprovalMissingException a("r.txt", "a.txt" );
    std::string expected = "Failed Approval: \nApproval File Not Found \nFile: \"a.txt\"";
    REQUIRE(a.what() == expected );
}

TEST_CASE("ApprovalMismatchExceptionHasAMessage") {
    ApprovalTests::ApprovalMismatchException a("r.txt", "a.txt" );
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
    bool exception_caught = false;
    try {
        ApprovalTests::Approvals::verify("foo", QuietReporter());
    }
    catch (const ApprovalTests::ApprovalMissingException&)
    {
        exception_caught = true;
    }
    catch (const ApprovalTests::ApprovalException&)
    {
        exception_caught = false;
    }
    REQUIRE(exception_caught == true);
}
