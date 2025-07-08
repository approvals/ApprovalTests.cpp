#pragma once
#ifdef FMT_VERSION

#include <fmt/format.h> // for fmt::to_string()

namespace ApprovalTests
{
    class FmtToString
    {
    public:
        template <typename T> static std::string toString(const T& printable)
        {
            return fmt::to_string(printable);
        }
    };

}
#endif
