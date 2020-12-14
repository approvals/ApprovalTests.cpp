#pragma once

#include <ApprovalTests.hpp>
#include "ApprovalTests/core/FileApprover.h"

namespace ApprovalTests
{
    class FrameworkIntegrations
    {
    public:
        static void
        setTestPassedNotification(FileApprover::TestPassedNotification notification);

        static void setCurrentTest(ApprovalTests::TestName* currentTest);
    };
}
