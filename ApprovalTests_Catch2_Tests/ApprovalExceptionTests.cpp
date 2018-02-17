#include "Catch.hpp"
#include "../ApprovalTests/ApprovalTests.h"

using namespace std;

TEST_CASE("ApprovalMissingExceptionHasAMessage") {
    ApprovalMissingException a( "r.txt", "a.txt" );
    string expected = "Failed Approval: \nApproval File Not Found \nFile: \"a.txt\"";
    REQUIRE(a.what() == expected );
}

TEST_CASE("ApprovalMismatchExceptionHasAMessage") {
    ApprovalMismatchException a( "r.txt", "a.txt" );
    string expected = "Failed Approval: \n"
            "Received does not match approved \n"
            "Received : \"r.txt\" \n"
            "Approved : \"a.txt\"";
    REQUIRE(a.what() == expected);
}
