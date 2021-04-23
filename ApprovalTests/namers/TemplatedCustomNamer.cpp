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

        using namespace ApprovalTests;

        // clang-format off
        result = replaceIfContains(result, fileExtension, [&](){return extensionWithDot.substr(1);});
        result = replaceIfContains(result, testFileName, [&](){return namer_.getSourceFileName();});
        result = replaceIfContains(result, testCaseName, [&](){return namer_.getTestName();});
        result = replaceIfContains(result, testSourceDirectory, [&](){return namer_.getDirectory();});
        result = replaceIfContains(result, approvedOrReceived, [&](){return approvedOrReceivedReplacement;});
        // clang-format on

        // Convert to native directory separators:
        return Path(result).toString();
    }

    std::string TemplatedCustomNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return constructFromTemplate(extensionWithDot, "approved");
    }

    std::string TemplatedCustomNamer::getReceivedFile(std::string extensionWithDot) const
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
