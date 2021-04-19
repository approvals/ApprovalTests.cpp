#include "TemplatedCustomNamer.h"
#include "ApprovalTests//utilities/StringUtils.h"

namespace ApprovalTests
{
    TemplatedCustomNamer::TemplatedCustomNamer(const std::string& templateString)
        : template_(templateString)
    {
    }
    std::string TemplatedCustomNamer::constructFromTemplate(
        const std::string& extensionWithDot,
        const std::string& approvedOrReceivedReplacement) const
    {
        std::string result = template_;
        // begin-snippet: custom_namer_tags
        auto testSourceDirectory = "{TestSourceDirectory}";
        auto testFileName = "{TestFileName}";
        auto testCaseName = "{TestCaseName}";
        auto approvedOrReceived = "{ApprovedOrReceived}";
        auto fileExtension = "{FileExtension}";
        // end-snippet

        result = ApprovalTests::StringUtils::replaceAll(
            result, fileExtension, extensionWithDot.substr(1));
        result = ApprovalTests::StringUtils::replaceAll(
            result, testFileName, namer_.getSourceFileName());
        result = ApprovalTests::StringUtils::replaceAll(
            result, testCaseName, namer_.getTestName());
        result = ApprovalTests::StringUtils::replaceAll(
            result, testSourceDirectory, namer_.getDirectory());
        result = ApprovalTests::StringUtils::replaceAll(
            result, approvedOrReceived, approvedOrReceivedReplacement);
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
