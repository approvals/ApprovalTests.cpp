
#include "TemplatedCustomNamer.h"

namespace ApprovalTests
{
    TemplatedCustomNamer::TemplatedCustomNamer(const std::string& templateString)
        : template_(templateString)
    {
    }
    std::string TemplatedCustomNamer::constructFromTemplate(
        const std::string& extensionWithDot, const std::string& approvedOrReceived) const
    {
        std::string result = template_;
        result = ApprovalTests::StringUtils::replaceAll(
            result, "{FileExtension}", extensionWithDot.substr(1));
        result = ApprovalTests::StringUtils::replaceAll(
            result, "{TestFileName}", namer_.getSourceFileName());
        result = ApprovalTests::StringUtils::replaceAll(
            result, "{TestCaseName}", namer_.getTestName());
        result = ApprovalTests::StringUtils::replaceAll(
            result, "{TestSourceDirectory}", namer_.getDirectory());
        result = ApprovalTests::StringUtils::replaceAll(
            result, "{ApprovedOrReceived}", approvedOrReceived);
        return result;
    }

    std::string TemplatedCustomNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return constructFromTemplate(extensionWithDot, "approved");
    }

    std::string TemplatedCustomNamer::getReceivedFile(std::string extensionWithDot) const
    {
        return constructFromTemplate(extensionWithDot, "received");
    }
}
