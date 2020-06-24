#include "ApprovalTests/reporters/TextDiffReporter.h"

namespace ApprovalTests
{
    TextDiffReporter::TextDiffReporter()
    {
        std::vector<std::shared_ptr<Reporter>> reporters = {
            CustomReporter::createForegroundReporter("diff"),
            CustomReporter::createForegroundReporter("C:/Windows/System32/fc.exe")};
        m_reporter = std::unique_ptr<Reporter>(new FirstWorkingReporter(reporters));
    }

    bool TextDiffReporter::report(std::string received, std::string approved) const
    {
        std::cout << "Comparing files:" << std::endl;
        std::cout << "received: " << received << std::endl;
        std::cout << "approved: " << approved << std::endl;
        const bool result = m_reporter->report(received, approved);
        if (!result)
        {
            std::cout << "TextDiffReporter did not find a working diff "
                         "program\n\n";
        }

        return result;
    }
}
