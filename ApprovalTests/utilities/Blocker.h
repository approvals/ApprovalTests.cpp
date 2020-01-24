#ifndef APPROVALTESTS_CPP_BLOCKER_H
#define APPROVALTESTS_CPP_BLOCKER_H

// Force the include with Version information to appear at the start
// of the release single-header.
#include "ApprovalTestsVersion.h"

namespace ApprovalTests
{
    class Blocker
    {
    public:
        Blocker() = default;
        Blocker(const Blocker&) = default;
        Blocker(Blocker&&) = default;
        Blocker& operator=(const Blocker&) = default;
        Blocker& operator=(Blocker&&) = default;

        virtual ~Blocker() = default;

        virtual bool isBlockingOnThisMachine() const = 0;
    };
}

#endif //APPROVALTESTS_CPP_BLOCKER_H
