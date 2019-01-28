#include <ostream>
#include "Catch.hpp"
#include "../ApprovalTests/Approvals.h"

using namespace std;



TEST_CASE("YouCanVerifyText") {
    Approvals::verify("My objects!");
}

TEST_CASE("TestStreamableObject") {
    Approvals::verify(42);
}

class NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& x) = delete; // prevent copy construction

    friend ostream &operator<<(ostream &os, const NonCopyable &copyable) {
        return os << 999;
    }
};

TEST_CASE("TestNonCopyableStreamableObject") {
    NonCopyable object;
    Approvals::verify(object);
}
