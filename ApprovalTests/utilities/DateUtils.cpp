#include "DateUtils.h"
#include "StringUtils.h"

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
    DateUtils::createUtcDateTime(int year,
                                 int month,
                                 int day,
                                 int hour,
                                 int minute,
                                 int second) // these are UTC values
    {
        tm timeinfo = createTm(year, month, day, hour, minute, second);
        time_t tt = toUtc(timeinfo);
        return std::chrono::system_clock::from_time_t(tt);
    }

    std::string DateUtils::toString(const std::chrono::system_clock::time_point& dateTime)
    {
        return toString(dateTime, "%a %Y-%m-%d %H:%M:%S UTC");
    }

    std::string DateUtils::toString(const std::chrono::system_clock::time_point& dateTime,
                                    const std::string& format)
    {
        time_t tt = std::chrono::system_clock::to_time_t(dateTime);
        tm tm_value = toUtc(tt);

        return StringUtils::toString(std::put_time(&tm_value, format.c_str()));
    }

    time_t DateUtils::toUtc(std::tm& timeinfo)
    {
#ifdef _WIN32
        std::time_t tt = _mkgmtime(&timeinfo);
#else
        time_t tt = timegm(&timeinfo);
#endif
        return tt;
    }

    tm DateUtils::toUtc(time_t& tt)
    {
#ifdef _MSC_VER // Visual Studio compiler
        std::tm tm_value = {};
        gmtime_s(&tm_value, &tt);
#else
        tm tm_value = *gmtime(&tt);
#endif
        return tm_value;
    }
}
