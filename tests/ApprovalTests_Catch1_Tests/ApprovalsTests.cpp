#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"

TEST_CASE("YouCanVerifyText") {
    ApprovalTests::Approvals::verify("My objects!");
}

