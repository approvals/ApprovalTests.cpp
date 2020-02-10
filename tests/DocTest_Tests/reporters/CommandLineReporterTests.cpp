#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "ApprovalTests/reporters/CustomReporter.h"

#include <vector>

using namespace ApprovalTests;

TEST_CASE("Test Command Lines")
{
    std::stringstream stream;
    std::vector<std::shared_ptr<GenericDiffReporter>> reporters = {
        // Mac
        std::make_shared<Mac::BeyondCompareReporter>(),
        std::make_shared<Mac::DiffMergeReporter>(),
        std::make_shared<Mac::KaleidoscopeReporter>(),
        std::make_shared<Mac::P4MergeReporter>(),
        std::make_shared<Mac::KDiff3Reporter>(),
        std::make_shared<Mac::TkDiffReporter>(),
        std::make_shared<Mac::VisualStudioCodeReporter>(),

        // Windows
        std::make_shared<Windows::TortoiseTextDiffReporter>(),
        std::make_shared<Windows::TortoiseImageDiffReporter>(),
        std::make_shared<Windows::TortoiseGitTextDiffReporter>(),
        std::make_shared<Windows::TortoiseGitImageDiffReporter>(),
        std::make_shared<Windows::BeyondCompare3Reporter>(),
        std::make_shared<Windows::BeyondCompare4Reporter>(),
        std::make_shared<Windows::WinMergeReporter>(),
        std::make_shared<Windows::AraxisMergeReporter>(),
        std::make_shared<Windows::CodeCompareReporter>(),
        std::make_shared<Windows::KDiff3Reporter>(),
        std::make_shared<Windows::VisualStudioCodeReporter>(),

        // Linux
        std::make_shared<Linux::MeldReporter>(),
        std::make_shared<Linux::KDiff3Reporter>()};
    for (const auto& reporter : reporters)
    {
        reporter->useCygwinConversions(false);
        stream << "native: " << reporter->getCommandLine("a.txt", "b.txt")
               << '\n';

        reporter->useCygwinConversions(true);
        stream << "cygwin: " << reporter->getCommandLine("a.txt", "b.txt")
               << '\n';
        stream << '\n';
    }
    Approvals::verify(stream.str());
}
