#pragma once

#include <string>

// Force the include with Version information to appear at the start
// of the release single-header.
#include "ApprovalTestsVersion.h"

namespace ApprovalTests
{
    /*! \brief Reporters are called on test failure, typically to show differences.

     Most reporters launch an external diffing tool, allowing programmers
     to understand the difference(s) between approved and received files. They
     also typically allow the output to be "approved".

     For an demonstration of this, see the
     <a href="https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Tutorial.md#top">Tutorial</a>.

     \see For more information, see
     <a href="https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Reporters.md#top">Reporter</a>
     in the User Guide on GitHub.
     */
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
