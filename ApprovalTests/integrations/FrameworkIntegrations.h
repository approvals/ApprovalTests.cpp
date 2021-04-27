#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/core/FileApprover.h"

namespace ApprovalTests
{
    class FrameworkIntegrations
    {
    public:
        static void
        setTestPassedNotification(FileApprover::TestPassedNotification notification);

        static void setCurrentTest(ApprovalTests::TestName* currentTest);

        static void registerRootDirectoryFromMainFile()
        {
#ifdef __BASE_FILE__
            TestName::registerRootDirectoryFromMainFile(__BASE_FILE__);
#endif
        }
    };
}
