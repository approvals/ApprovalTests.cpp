#pragma once

#include <chrono>
#include <string>

namespace ApprovalTests
{
    // All values are in UTC
    class DateUtils
    {
    public:
        static std::tm
        createTm(int year, int month, int day, int hour, int minute, int second);

        static std::chrono::system_clock::time_point
        createUtcDateTime(int year, int month, int day, int hour, int minute, int second);

        static std::string toString(const std::chrono::system_clock::time_point& dateTime,
                                    const std::string& format);

        static std::string
        toString(const std::chrono::system_clock::time_point& dateTime);

        static time_t toUtc(std::tm& timeinfo);

        static tm toUtc(time_t& tt);
    };
}
