#define APPROVALS_UT
#include "ApprovalTests.hpp"

int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

    // This puts "received" and "approved" files in approval_tests/ sub-directory,
    // keeping the test source directory tidy:
    auto directory = Approvals::useApprovalsSubdirectory("approval_tests");

    "Starter"_test = []() {
        // TODO Replace 42 with the value or object whose contents you are verifying.
        // For help, see:
        // https://approvaltestscpp.readthedocs.io/en/latest/generated_docs/ToString.html
        Approvals::verify(42);
    };
}
