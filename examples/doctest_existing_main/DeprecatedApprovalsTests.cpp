// These are tests to ensure that we are maintaining the pre-Options
// interface, i.e. methods that take a Reporter as the last argument.

#undef APPROVAL_TESTS_HIDE_DEPRECATED_CODE
#undef APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS

#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"

#include <list>

using namespace ApprovalTests;

TEST_CASE("verify")
{
    DefaultReporter reporter;

    SUBCASE("string Reporter")
    {
        const std::string input = R"(
        static void verify(std::string contents, const Reporter& reporter)
    )";
        Approvals::verify(input, reporter);
    }

    SUBCASE("writer Reporter")
    {
        const std::string input = R"(
        static void verify(const ApprovalWriter& writer, const Reporter& reporter)
    )";
        StringWriter writer(input, ".md");
        Approvals::verify(writer, reporter);
    }

    SUBCASE("T Reporter")
    {
        Approvals::verify(42, reporter);
    }

    SUBCASE("T converter Reporter")
    {
        Approvals::verify(
            42, [](auto value, auto& os) { os << "**value:** " << value; }, reporter);
    }
}

TEST_CASE("verifyWithExtension")
{
    DefaultReporter reporter;

    SUBCASE("string string Reporter")
    {
        const std::string input = R"(
        static void verifyWithExtension(std::string contents,
                                        const std::string& fileExtensionWithDot,
                                        const Reporter& reporter)
    )";
        // This needs to be an extension that CLion won't try and reformat upon commit:
        Approvals::verifyWithExtension(input, ".xyz", reporter);
    }

    SUBCASE("T string Reporter")
    {
        Approvals::verifyWithExtension(42, ".csv", reporter);
    }

    SUBCASE("T converter string Reporter")
    {
        Approvals::verifyWithExtension(
            42,
            [](auto value, auto& os) { os << "**value:** " << value; },
            ".md",
            reporter);
    }
}

TEST_CASE("verifyExceptionMessage.function Reporter")
{
    Approvals::verifyExceptionMessage(
        []() { throw std::runtime_error("Here is my exception message"); },
        DefaultReporter());
}

TEST_CASE("verifyAll")
{
    DefaultReporter reporter;

    {
        const std::list<int> values{1, 2, 3};
        auto converter = [](auto value, auto& os) { os << "**value:** " << value; };

        SUBCASE("header start finish converter Reporter")
        {
            Approvals::verifyAll("list", begin(values), end(values), converter, reporter);
        }

        SUBCASE("header container converter Reporter")
        {
            Approvals::verifyAll("list", values, converter, reporter);
        }
    }

    {
        const std::vector<int> values{1, 2, 3};

        SUBCASE("header vector Reporter")
        {
            Approvals::verifyAll("vector<int>", values, reporter);
        }

        SUBCASE("vector Reporter")
        {
            Approvals::verifyAll(values, reporter);
        }
    }
}

TEST_CASE("verifyExistingFile")
{
    ApprovalTestNamer namer;
    Approvals::verifyExistingFile(
        namer.getDirectory() + "../../tests/DocTest_Tests/sample.txt", DefaultReporter());
}
