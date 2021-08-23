#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

#include <iostream> // needed to fix linker error on XCode Release builds
#include "ApprovalTests/Approvals.h"

#include <cstdlib>

namespace
{
    int random(int max)
    {
        return std::rand() % max;
    }
}

TEST_CASE("createRegexScrubber")
{
    // begin-snippet: complex_regex_scrubbing
    auto input = "1) Hello 1234 World";
    auto scrubber = ApprovalTests::Scrubbers::createRegexScrubber(
        std::regex(R"(\d+)"), [](const auto& match) {
            auto match_text = match.str();
            auto match_integer = std::stoi(match_text);
            if (match_integer < 10)
            {
                return match_text;
            }
            else
            {
                return std::string("[number]");
            }
        });
    // end-snippet
    ApprovalTests::Approvals::verify(input, ApprovalTests::Options(scrubber));
}

TEST_CASE("createRegexScrubber with fixed result")
{
    using namespace ApprovalTests;
    auto input = "Hello 1234 World";
    auto scrubber = Scrubbers::createRegexScrubber(std::regex(R"(\d+)"), "number");
    Approvals::verify(input, Options(scrubber));
}

TEST_CASE("createRegexScrubber with string input and fixed result")
{
    // begin-snippet: simple_regex_scrubbing
    using namespace ApprovalTests;
    std::stringstream os;
    os << "Hello " << random(1000) << " World";
    Approvals::verify(os.str(),
                      Options(Scrubbers::createRegexScrubber(R"(\d+)", "[number]")));
    // end-snippet
}

TEST_CASE("regex scrubber")
{
    using namespace ApprovalTests;
    auto input = "9012 Hello 1234 World 1234 5678";
    auto scrubber =
        Scrubbers::scrubRegex(input, std::regex(R"(\d\d\d\d)"), [](const auto& match) {
            return "number(" + match.str() + ")\n";
        });
    Approvals::verify(scrubber);
}

TEST_CASE("regex scrubber with full customisation")
{
    auto input = "9012 Hello 1234 World 1234 5678";
    ApprovalTests::Scrubber scrubber = [](const std::string& text) {
        return ApprovalTests::Scrubbers::scrubRegex(
            text, std::regex(R"(\d\d\d\d)"), [](const auto& match) {
                return "number(" + match.str() + ")\n";
            });
    };
    // begin-snippet: scrubber_in_options_object
    ApprovalTests::Approvals::verify(input,
                                     ApprovalTests::Options().withScrubber(scrubber));
    // end-snippet
}

TEST_CASE("regex scrubber with empty input does not loop endlessly")
{
    using namespace ApprovalTests;

    const char* input = "hello";
    {
        auto scrubber = Scrubbers::createRegexScrubber("", "[replacement]");
        CHECK(scrubber(input) == input);
    }
    {
        auto scrubber = Scrubbers::createRegexScrubber("R()", "[replacement]");
        CHECK(scrubber(input) == input);
    }
}
