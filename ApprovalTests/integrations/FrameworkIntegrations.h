#pragma once

#include "ApprovalTests/core/FileApprover.h"

namespace ApprovalTests
{
    class FrameworkIntegrations
    {
    public:
        static void
        setTestPassedNotification(FileApprover::TestPassedNotification notification);
    };
}
