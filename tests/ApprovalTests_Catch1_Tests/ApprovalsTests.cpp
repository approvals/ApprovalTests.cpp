#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"

TEST_CASE("YouCanVerifyText") {
    Approvals::verify("My objects!");
}

