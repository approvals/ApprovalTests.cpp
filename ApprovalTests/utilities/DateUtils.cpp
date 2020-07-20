#include "DateUtils.h"

#include <sstream>
#include <iomanip>

namespace ApprovalTests
{
    std::tm
    DateUtils::createTm(int year, int month, int day, int hour, int minute, int second)
    {
        std::tm timeinfo = tm();
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_mday = day;
        timeinfo.tm_hour = hour;
        timeinfo.tm_min = minute;
        timeinfo.tm_sec = second;
        return timeinfo;
    }

    std::chrono::system_clock::time_point
    DateUtils::createDateTime(int year,
                              int month,
                              int day,
                              int hour,
                              int minute,
                              int second) // these are UTC values
    {
        tm timeinfo = createTm(year, month, day, hour, minute, second);
        std::time_t tt = timegm(&timeinfo);
        return std::chrono::system_clock::from_time_t(tt);
    }

    std::string DateUtils::toString(const std::chrono::system_clock::time_point& dateTime)
    {
        return toString(dateTime, "%a %Y-%m-%d %H:%M:%S UTC");
    }

    std::string DateUtils::toString(const std::chrono::system_clock::time_point& dateTime,
                                    const std::string& format)
    {
        std::string result;
        time_t tt = std::chrono::system_clock::to_time_t(dateTime);
        tm tm = *gmtime(&tt); // GMT (UTC)
        std::stringstream ss;
        ss << std::put_time(&tm, format.c_str());
        result = ss.str();
        return result;
    }
}
