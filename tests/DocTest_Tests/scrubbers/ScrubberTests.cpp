#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

#include <iostream> // needed to fix linker error on XCode Release builds
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/QuietReporter.h"

#include <cstdlib>

using namespace ApprovalTests;

TEST_CASE("test createRegexScrubber")
{
    auto input = "Hello 1234 World";
    auto output = Scrubbers::createRegexScrubber(
        std::regex("1234"), [](const auto& /*match*/) { return "number"; });
    Approvals::verify(input, Options(output));
}

TEST_CASE("test createRegexScrubber with fixed result")
{
    auto input = "Hello 1234 World";
    auto output = Scrubbers::createRegexScrubber(std::regex(R"(\d+)"), "number");
    Approvals::verify(input, Options(output));
}

TEST_CASE("test createRegexScrubber with string input and fixed result")
{
    auto input = std::string("Hello ") + std::to_string(std::rand() % 1000) + " World";
    Approvals::verify(input,
                      Options(Scrubbers::createRegexScrubber(R"(\d+)", "[number]")));
}

TEST_CASE("regex scrubber")
{
    auto input = "9012 Hello 1234 World 1234 5678";
    auto scrubbed =
        Scrubbers::scrubRegex(input, std::regex(R"(\d\d\d\d)"), [](const auto& match) {
            return "number(" + match.str() + ")\n";
        });
    Approvals::verify(scrubbed);
}
