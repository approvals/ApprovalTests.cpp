// begin-snippet: ut_main
#define APPROVALS_UT
#include "ApprovalTests.hpp"
// end-snippet

int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

    auto directory = Approvals::useApprovalsSubdirectory("approval_tests");

    // begin-snippet: ut_main_usage
    "ItCanVerifyAFile"_test = []() {

        try {
            Approvals::verify("Approval Tests can verify text via the golden master method");
        }
        catch (const std::exception& e) {
            detail::log{} << e.what();
            expect(false);
        }
	};
    // end-snippet

    test("AnotherWayItCanVerifyAFile") = []() {
        try {
            Approvals::verify("Approval Tests can verify text via the golden master method");
        }
        catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
    };

    // begin-snippet: ut_main_multiple
    "ItCanUseMultipleVerify"_test = []() {
        try {
                auto section = NamerFactory::appendToOutputFilename("section 1");
                Approvals::verify("Approval Tests can verify text via the golden master method");
        }
        catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }

        try {
            auto section = NamerFactory::appendToOutputFilename("section 2");
            Approvals::verify("Approval Tests can verify text via the golden master method");
        }
        catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
    };
    // end-snippet

    "YouCanUseAWriter"_test = []() {
        // begin-snippet: ut_use_custom_writer
        try {
            using HtmlWriter = StringWriter;
            HtmlWriter writer("<h1>hello world</h1>", ".html");
            Approvals::verify(writer);
        }
        catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
        // end-snippet
    };

    "YouCanSpecifyYourFileExtension"_test = []() {
        // begin-snippet: ut_use_custom_file_extension
        try {
            Approvals::verifyWithExtension("<h1>hello world</h1>", ".html");
        }
            catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
        // end-snippet
    };

    "YouCanSpecifyYourFileExtensionWithToString"_test = []() {
        try {
            Approvals::verifyWithExtension(1337, ".csv");
        }
            catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
    };

    "YouCanSpecifyYourFileExtensionWithFormatter"_test = []() {
        try {
            Approvals::verifyWithExtension(1337, [](auto value, auto& os) {os << "**value:** " << value; }, ".md");
        }
        catch (const std::exception & e) {
            detail::log{} << e.what();
            expect(false);
        }
    };
}
