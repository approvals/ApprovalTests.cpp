#include "catch.1.9.0.hpp"
#include "ApprovalTests/Approvals.h"

using namespace std;

TEST_CASE("YouCanVerifyText") {
    Approvals::verify("My objects!");
}

