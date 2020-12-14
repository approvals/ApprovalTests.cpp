#include "FrameworkIntegrations.h"

namespace ApprovalTests
{
    void FrameworkIntegrations::setTestPassedNotification(
        FileApprover::TestPassedNotification notification)
    {
        FileApprover::setTestPassedNotification(notification);
    }

    void FrameworkIntegrations::setCurrentTest(ApprovalTests::TestName* currentTest)
    {
        ApprovalTestNamer::currentTest(currentTest);
    }
}
