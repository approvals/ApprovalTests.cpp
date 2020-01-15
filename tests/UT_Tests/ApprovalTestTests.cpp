// begin-snippet: ut_main
#define APPROVALS_UT
#include "ApprovalTests.hpp"
// end-snippet

#include "tests/Catch2_Tests/reporters/FakeReporter.h"

int main()
{
    using namespace boost::ut;
    using namespace ApprovalTests;

    auto directory = Approvals::useApprovalsSubdirectory("approval_tests");

    "ItReportsAndThrowsIfVerifyFails"_test = []() {
        auto front_loader = std::make_shared<FakeReporter>(true);

        // Use a front-loaded reporter so this is used even we are running
        // in a CI system.
        auto front_loaded_reporter_disposer =
            Approvals::useAsFrontLoadedReporter(front_loader);

        bool approvalMissingExceptionReceived = false;
        try
        {
            Approvals::verify("cucumber");
        }
        catch (const ApprovalMissingException&)
        {
            approvalMissingExceptionReceived = true;
        }
        catch (const std::exception& e)
        {
            expect(approvalMissingExceptionReceived == true_b)
                << "Unexpected exception received: " << e.what();
        }

        // If these start failing, run the tests with verbose on,
        // or ctest's --output-on-failure.
        // You will probably find that Boost.UT is unable to find the
        // name of the source file.
        // For ways to fix this, see:
        // https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
        expect(approvalMissingExceptionReceived == true_b);
        expect(front_loader->called == true_b);
    };

    // begin-snippet: ut_main_usage
    "ItCanVerifyAFile"_test = []() {
        Approvals::verify(
            "Approval Tests can verify text via the golden master method");
    };
    // end-snippet

    test("AnotherWayItCanVerifyAFile") = []() {
        Approvals::verify(
            "Approval Tests can verify text via the golden master method");
    };

    // begin-snippet: ut_main_multiple
    "ItCanUseMultipleVerify"_test = []() {
        {
            // Here we simulate test sections, so that Approval Tests uses different
            // output file names for the different verify() calls.
            auto section = NamerFactory::appendToOutputFilename("section 1");
            Approvals::verify(
                "Approval Tests can verify text via the golden master method");
        }
        {
            auto section = NamerFactory::appendToOutputFilename("section 2");
            Approvals::verify("Approval Tests can verify different text via "
                              "the golden master method");
        }
    };
    // end-snippet

    "YouCanUseAWriter"_test = []() {
        // begin-snippet: ut_use_custom_writer
        using HtmlWriter = StringWriter;
        HtmlWriter writer("<h1>hello world</h1>", ".html");
        Approvals::verify(writer);
        // end-snippet
    };

    "YouCanSpecifyYourFileExtension"_test = []() {
        // begin-snippet: ut_use_custom_file_extension
        Approvals::verifyWithExtension("<h1>hello world</h1>", ".html");
        // end-snippet
    };

    "YouCanSpecifyYourFileExtensionWithToString"_test = []() {
        Approvals::verifyWithExtension(1337, ".csv");
    };

    "YouCanSpecifyYourFileExtensionWithFormatter"_test = []() {
        Approvals::verifyWithExtension(
            1337,
            [](auto value, auto& os) { os << "**value:** " << value; },
            ".md");
    };
}
