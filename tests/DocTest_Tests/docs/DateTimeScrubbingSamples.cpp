#include "doctest/doctest.h"

#include "utilities/DateUtils.h"
#include "Approvals.h"

using namespace ApprovalTests;

namespace
{
    void verifyDateAndTimeString(const std::string& dateRegex,
                                 const std::string& textWithDate)
    {
        INFO("textWithDate " << textWithDate);
        INFO("dateRegex " << dateRegex);

        auto scrubber = Scrubbers::createRegexScrubber(dateRegex, "[date_and_time]");
        CHECK("date: [date_and_time]" == scrubber(textWithDate));

        Approvals::verify(textWithDate, Options().withScrubber(scrubber));
    }

}

TEST_CASE("Test DateTime scrubbing - with default format")
{
    // Thu 2020-08-06 11:28:33 UTC
    const auto dateTime = std::chrono::system_clock::now();

    std::string weekDay = R"([A-Za-z]{3})";

    std::string date = R"(\d\d\d\d-\d\d-\d\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string time_zone = "UTC";

    const auto dateRegex = weekDay + " " + date + " " + time + " " + time_zone;

    std::string textWithDate = "date: " + DateUtils::toString(dateTime);
    verifyDateAndTimeString(dateRegex, textWithDate);
}

TEST_CASE("Test DateTime scrubbing - with specific format")
{
    // Mon Jun 22 14:07:34 2020
    const auto dateTime = std::chrono::system_clock::now();
    const char* format =
        "%a %b %d %H:%M:%S %Y"; // g++ on mingw does not properly format "%a %b %e %T %G"

    std::string weekDay = R"([A-Za-z]{3})";
    std::string month = R"([A-Za-z]{3})";
    std::string date = R"([\d ]\d)";
    std::string time = R"(\d\d:\d\d:\d\d)";
    std::string year = R"(\d\d\d\d)";
    const auto dateRegex = weekDay + " " + month + " " + date + " " + time + " " + year;

    std::string textWithDate = "date: " + DateUtils::toString(dateTime, format);
    verifyDateAndTimeString(dateRegex, textWithDate);
}
