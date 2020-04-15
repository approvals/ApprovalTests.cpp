#pragma once

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
