// begin-snippet: ut_main
// main.cpp:
#define APPROVALS_UT
#include "ApprovalTests.hpp"
// end-snippet

// begin-snippet: ut_main_usage
// main.cpp:
int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

	"Approval"_test = []() {
        expect(nothrow([] {
            Approvals::verify("Approval Tests can verify text via the golden master method");
        }));
	};
}
// end-snippet


// begin-snippet: ut_main_multiple
// main.cpp:
int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

	"Approval"_test = []() {
        expect(nothrow([] { 
            auto section = NamerFactory::appendToOutputFilename("test 1");
            Approvals::verify("First Approval Test"); 
        }));

        expect(nothrow([] { 
            auto section = NamerFactory::appendToOutputFilename("test 2");
            Approvals::verify("Second Approval Test"); 
        }));
    };
}
// end-snippet
