#define APPROVALS_UT
#include "ApprovalTests.hpp"

int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

	"ItCanVerifyAFile"_test = []() {
        expect(nothrow([] {
            Approvals::verify("Approval Tests can verify text via the golden master method");
        })) <<  "File verification error on the [Boost].UT Test Framework";
	};
}
