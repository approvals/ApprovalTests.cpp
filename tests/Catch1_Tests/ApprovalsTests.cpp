#include "Catch.hpp"
#include "ApprovalTests/Approvals.h"

using namespace ApprovalTests;

TEST_CASE("YouCanVerifyText") {
    Approvals::verify("My objects!");
}

