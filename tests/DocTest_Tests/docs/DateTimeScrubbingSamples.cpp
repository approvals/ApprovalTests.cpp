#include "doctest/doctest.h"

#include "utilities/DateUtils.h"
#include "Approvals.h"

using namespace ApprovalTests;

TEST_CASE("Test DateTime scrubbing - with default format")
{
    // Thu 2020-08-06 11:28:33 UTC
    std::string textWithDate =
        "date: " + DateUtils::toString(std::chrono::system_clock::now());
    std::string weekDay = R"([A-Za-z]{3})";

    std::string year = R"(\d\d\d\d)";
    std::string month = R"(\d\d)";
    std::string date = R"(\d\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string time_zone = "UTC";

    const auto dateRegex =
        weekDay + " " + year + "-" + month + "-" + date + " " + time + " " + time_zone;

    auto scrubber = Scrubbers::createRegexScrubber(dateRegex, "[date_and_time]");
    CHECK("date: [date_and_time]" == scrubber(textWithDate));

    Approvals::verify(textWithDate, Options().withScrubber(scrubber));
}

TEST_CASE("Test DateTime scrubbing - with specific format")
{
    // Mon Jun 22 14:07:34 2020
    // %a  %b  %e %H:%M:%S %G
    std::string textWithDate =
        "date: " +
        DateUtils::toString(std::chrono::system_clock::now(), "%a %b %e %T %G");

    std::string weekDay = R"([A-Za-z]{3})";
    std::string month = R"([A-Za-z]{3})";
    std::string date = R"([\d ]\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string year = R"(\d\d\d\d)";
    const auto dateRegex = weekDay + " " + month + " " + date + " " + time + " " + year;

    auto scrubber = Scrubbers::createRegexScrubber(dateRegex, "[date_and_time]");
    CHECK("date: [date_and_time]" == scrubber(textWithDate));

    Approvals::verify(textWithDate, Options().withScrubber(scrubber));
}
