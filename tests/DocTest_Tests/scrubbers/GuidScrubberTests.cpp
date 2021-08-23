#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"
#include "ApprovalTests/utilities/StringUtils.h"

#include <iostream> // needed to fix linker error on XCode Release builds
#include "ApprovalTests/Approvals.h"

TEST_CASE("Input with single GUID")
{
    auto input = "2fd78d4a-ad49-447d-96a8-deda585a9aa5 and normal text";
    auto output = ApprovalTests::Scrubbers::scrubGuid(input);
    REQUIRE(output == "guid_1 and normal text");
}

TEST_CASE("Input with no GUIDs")
{
    auto input = "";
    auto output = ApprovalTests::Scrubbers::scrubGuid(input);
    REQUIRE(output == "");
}

TEST_CASE("Input with non-GUID")
{
    std::string input = "hello world";
    auto output = ApprovalTests::Scrubbers::scrubGuid(input);
    REQUIRE(output == input);
}

TEST_CASE("Input with multiple GUIDs")
{
    // begin-snippet: guid_scrubbing
    using namespace ApprovalTests;
    std::string jsonFromRestCall = R"(
        {
            child: {
                id: b34b4da8-090e-49d8-bd35-7e79f633a2ea
                parent1: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
                parent2: 05f77de3-3790-4d45-b045-def96c9cd371
            }
            person: {
                name: mom
                id: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
            }
            person: {
                name: dad
                id: 05f77de3-3790-4d45-b045-def96c9cd371
            }
        }
        )";
    Approvals::verify(jsonFromRestCall, Options().withScrubber(Scrubbers::scrubGuid));
    // end-snippet
}

TEST_CASE("Scrubbing in verifyAll")
{
    std::vector<std::string> v{"b34b4da8-090e-49d8-bd35-7e79f633a2ea",
                               "2fd78d4a-ad49-447d-96a8-deda585a9aa5",
                               "b34b4da8-090e-49d8-bd35-7e79f633a2ea"};
    // begin-snippet: basic_approval_with_scrubber
    using namespace ApprovalTests;
    Approvals::verifyAll("IDs", v, Options(Scrubbers::scrubGuid));
    // end-snippet
}

TEST_CASE("Scrubbing in verifyAll-2")
{
    std::vector<std::string> v{"b34b4da8-090e-49d8-bd35-7e79f633a2ea",
                               "2fd78d4a-ad49-447d-96a8-deda585a9aa5",
                               "b34b4da8-090e-49d8-bd35-7e79f633a2ea"};
    // begin-snippet: basic_approval_with_scrubber_2
    using namespace ApprovalTests;
    Approvals::verifyAll("IDs", v, Options().withScrubber(Scrubbers::scrubGuid));
    // end-snippet
}

TEST_CASE("Scrubbing via Lambda")
{
    // clang-format off
    // begin-snippet: scrubbing_via_lambda
    using namespace ApprovalTests;
    Approvals::verify(
        "1 2 3 4 5 6",
        Options().withScrubber(
            [](const std::string& t) {return StringUtils::replaceAll(t, "3", "Fizz");}
        ));
    // end-snippet
    // clang-format on
}
