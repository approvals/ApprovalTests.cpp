#include "ApprovalTests/reporters/TextDiffReporter.h"
#include "ApprovalTests/reporters/CustomReporter.h"
#include "ApprovalTests/reporters/FirstWorkingReporter.h"

#include <iostream>

namespace ApprovalTests
{
    TextDiffReporter::TextDiffReporter() : TextDiffReporter(std::cout)
    {
    }

    TextDiffReporter::TextDiffReporter(std::ostream& stream) : stream_(stream)
    {
        std::vector<std::shared_ptr<Reporter>> reporters = {
            CustomReporter::createForegroundReporter("diff", Type::TEXT, true),
            CustomReporter::createForegroundReporter(
                "C:/Windows/System32/fc.exe", Type::TEXT_AND_IMAGE, true)};
        m_reporter = std::unique_ptr<Reporter>(new FirstWorkingReporter(reporters));
    }

    bool TextDiffReporter::report(std::string received, std::string approved) const
    {
        stream_ << "Comparing files:" << std::endl;
        stream_ << "received: " << received << std::endl;
        stream_ << "approved: " << approved << std::endl;
        const bool result = m_reporter->report(received, approved);
        if (!result)
        {
            stream_ << "TextDiffReporter did not find a working diff "
                       "program\n\n";
        }

        return result;
    }
}
