#include "doctest/doctest.h"
#include "ApprovalTests/scrubbers/Scrubbers.h"

#include <iostream> // needed to fix linker error on XCode Release builds
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/QuietReporter.h"

using namespace ApprovalTests;

//TEST_CASE("regex scrubber")
//{
//    auto input = "Hello 1234 World";
//    auto output = Scrubbers::createRegexScrubber("1234", "number");
//    auto output = Scrubbers::createRegexScrubber("1234", [](const std::string& /*match*/){ return "number";});
//    auto output = [](auto text){
//        return Scrubbers::scrubRegex(text, "1234", [](const std::string&){ return "number";})
//    };
//    REQUIRE(output == "guid_1 and normal text");
//    Approvals::verify(input, Options(function));
//}

TEST_CASE("regex scrubber")
{
    auto input = "9012 Hello 1234 World 1234 5678";
    auto scrubbed =
        Scrubbers::scrubRegex(input, std::regex(R"(\d\d\d\d)"), [](const auto& match) {
            std::cout << match.str() << '\n';
            return "number(" + match.str() + ")\n";
        });
    Approvals::verify(scrubbed);
}
