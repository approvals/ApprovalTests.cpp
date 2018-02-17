#include "Catch.hpp"
#include "../ApprovalTests/Approvals.h"

using namespace std;



TEST_CASE("YouCanVerifyText") {
    Approvals::verify("My objects!");
}

TEST_CASE("TestStreamableObject") {
    Approvals::verify(42);
}

