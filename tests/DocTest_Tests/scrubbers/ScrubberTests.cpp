#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

#include <iostream> // needed to fix linker error on XCode Release builds
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/QuietReporter.h"

#include <cstdlib>
#include <chrono>

using namespace ApprovalTests;

namespace
{
    int random(int max)
    {
        return std::rand() % max;
    }
}

TEST_CASE("test createRegexScrubber")
{
    // begin-snippet: complex_regex_scrubbing
    auto input = "1) Hello 1234 World";
    auto scrubber =
        Scrubbers::createRegexScrubber(std::regex(R"(\d+)"), [](const auto& match) {
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
    Approvals::verify(input, Options(scrubber));
}

TEST_CASE("test createRegexScrubber with fixed result")
{
    auto input = "Hello 1234 World";
    auto scrubber = Scrubbers::createRegexScrubber(std::regex(R"(\d+)"), "number");
    Approvals::verify(input, Options(scrubber));
}

TEST_CASE("test createRegexScrubber with string input and fixed result")
{
    // begin-snippet: simple_regex_scrubbing
    std::stringstream os;
    os << "Hello " << random(1000) << " World";
    Approvals::verify(os.str(),
                      Options(Scrubbers::createRegexScrubber(R"(\d+)", "[number]")));
    // end-snippet
}

TEST_CASE("regex scrubber")
{
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
    Scrubber scrubber = [](const std::string& text) {
        return Scrubbers::scrubRegex(
            text, std::regex(R"(\d\d\d\d)"), [](const auto& match) {
                return "number(" + match.str() + ")\n";
            });
    };
    // begin-snippet: scrubber_in_options_object
    Approvals::verify(input, Options().withScrubber(scrubber));
    // end-snippet
}

TEST_CASE("test createRegexScrubber with date and time")
{
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::stringstream output;

#if defined(_MSC_VER)
#pragma warning(push)
// Suppress: warning C4996: 'ctime': This function or variable may be unsafe. Consider using ctime_s instead.
//                          To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.
#pragma warning(disable : 4996)
#endif

    output << "Today's date and time is " << std::ctime(&end_time);

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    // begin-snippet: scrubbing_date_and_time
    // Example of format that this matches:
    //  Tue Sep  3 16:58:52 2019
    const auto dateRegex = R"([A-Za-z]{3} [A-Za-z]{3} [\d ]\d \d\d:\d\d:\d\d \d\d\d\d)";

    Approvals::verify(
        output.str(),
        Options(Scrubbers::createRegexScrubber(dateRegex, "[date_and_time]")));
    // end-snippet
}
