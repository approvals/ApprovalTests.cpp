#include "TemplatedCustomNamer.h"
#include "ApprovalTests//utilities/Path.h"
#include "ApprovalTests//utilities/StringUtils.h"

#include <functional>
#include <utility>

namespace
{
    std::string replaceIfContains(std::string input,
                                  std::string pattern,
                                  std::function<std::string(void)> replacer)
    {
        if (!ApprovalTests::StringUtils::contains(input, pattern))
        {
            return input;
        }
        return ApprovalTests::StringUtils::replaceAll(input, pattern, replacer());
    }
}

namespace ApprovalTests
{
    TemplatedCustomNamer::TemplatedCustomNamer(std::string templateString)
        : template_(std::move(templateString))
    {
        if (!StringUtils::contains(template_, "{ApprovedOrReceived}"))
        {
            throw std::runtime_error(
                "Template must contain `{ApprovedOrReceived}` or the received and "
                "approved files will not be unique.\n"
                "Template: " +
                template_);
        }
    }

    Path TemplatedCustomNamer::constructFromTemplate(
        const std::string& extensionWithDot,
        const std::string& approvedOrReceivedReplacement) const
    {
        std::string result = template_;
        // begin-snippet: custom_namer_tags
        auto testSourceDirectory = "{TestSourceDirectory}";
        auto relativeTestSourceDirectory = "{RelativeTestSourceDirectory}";
        auto approvalsSubdirectory = "{ApprovalsSubdirectory}";
        auto testFileName = "{TestFileName}";
        auto testCaseName = "{TestCaseName}";
        auto approvedOrReceived = "{ApprovedOrReceived}";
        auto fileExtension = "{FileExtension}";
        // end-snippet

        using namespace ApprovalTests;

        // clang-format off
        result = replaceIfContains(result, fileExtension, [&](){return extensionWithDot.substr(1);});
        result = replaceIfContains(result, approvalsSubdirectory, [&](){return namer_.getApprovalsSubdirectory();});
        result = replaceIfContains(result, relativeTestSourceDirectory, [&](){return namer_.getRelativeTestSourceDirectory();});
        result = replaceIfContains(result, testFileName, [&](){return namer_.getSourceFileName();});
        result = replaceIfContains(result, testCaseName, [&](){return namer_.getTestName();});
        result = replaceIfContains(result, testSourceDirectory, [&](){return namer_.getTestSourceDirectory();});
        result = replaceIfContains(result, approvedOrReceived, [&](){return approvedOrReceivedReplacement;});
        // clang-format on

        // Convert to native directory separators:
        return Path(result);
    }

    std::string TemplatedCustomNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return getApprovedFileAsPath(extensionWithDot).toString();
    }

    std::string TemplatedCustomNamer::getReceivedFile(std::string extensionWithDot) const
    {
        return getReceivedFileAsPath(extensionWithDot).toString();
    }

    Path TemplatedCustomNamer::getApprovedFileAsPath(std::string extensionWithDot) const
    {
        return constructFromTemplate(extensionWithDot, "approved");
    }

    Path TemplatedCustomNamer::getReceivedFileAsPath(std::string extensionWithDot) const
    {
        return constructFromTemplate(extensionWithDot, "received");
    }

    std::shared_ptr<TemplatedCustomNamer>
    TemplatedCustomNamer::create(std::string templateString)
    {
        return std::make_shared<TemplatedCustomNamer>(templateString);
    }

    DefaultNamerDisposer
    TemplatedCustomNamer::useAsDefaultNamer(std::string templateString)
    {
        return Approvals::useAsDefaultNamer([=]() { return create(templateString); });
    }
}
