#pragma once

#include <string>

// Force the include with Version information to appear at the start
// of the release single-header.
#include "ApprovalTestsVersion.h"

namespace ApprovalTests
{
    class Reporter
    {
    public:
        virtual ~Reporter() = default;
        virtual bool report(std::string received, std::string approved) const = 0;
    };

    namespace Detail
    {
        //! Helper to prevent compilation failure when types are wrongly treated as Reporter:
        template <typename T, typename R = void>
        using EnableIfNotDerivedFromReporter = typename std::enable_if<
            !std::is_base_of<Reporter, typename std::decay<T>::type>::value,
            R>::type;
    } // namespace Detail
}
