#include "doctest/doctest.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/reporters/WindowsReporters.h"
#include "ApprovalTests/reporters/MacReporters.h"
#include "ApprovalTests/reporters/LinuxReporters.h"
#include "ApprovalTests/reporters/CrossPlatformReporters.h"

#include <vector>

std::string scrubProgramFiles(const std::string& output)
{
    using namespace ApprovalTests;
    auto scrubbed = output;
    for (const auto& path : DiffInfo::getProgramFileLocations())
    {
        scrubbed =
            StringUtils::replaceAll(scrubbed, path, DiffInfo::programFileTemplate());
    }
    return scrubbed;
}

TEST_CASE("Test Command Lines")
{
    using namespace ApprovalTests;
    std::stringstream stream;
    std::vector<std::shared_ptr<GenericDiffReporter>> reporters = {
        // begin-snippet: add_reporter_command_test
        // Mac
        std::make_shared<Mac::AraxisMergeReporter>(),
        std::make_shared<Mac::BeyondCompareReporter>(),
        std::make_shared<Mac::DiffMergeReporter>(),
        std::make_shared<Mac::KaleidoscopeReporter>(),
        std::make_shared<Mac::P4MergeReporter>(),
        std::make_shared<Mac::SublimeMergeReporter>(),
        std::make_shared<Mac::KDiff3Reporter>(),
        std::make_shared<Mac::TkDiffReporter>(),
        std::make_shared<Mac::VisualStudioCodeReporter>(),
        std::make_shared<Mac::CLionDiffReporter>(),
        // end-snippet

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
        std::make_shared<Windows::SublimeMergeReporter>(),
        std::make_shared<Windows::KDiff3Reporter>(),
        std::make_shared<Windows::VisualStudioCodeReporter>(),

        // Linux
        std::make_shared<Linux::BeyondCompareReporter>(),
        std::make_shared<Linux::MeldReporter>(),
        std::make_shared<Linux::SublimeMergeSnapReporter>(),
        std::make_shared<Linux::SublimeMergeFlatpakReporter>(),
        std::make_shared<Linux::SublimeMergeRepositoryPackageReporter>(),
        std::make_shared<Linux::SublimeMergeDirectDownloadReporter>(),
        std::make_shared<Linux::KDiff3Reporter>(),

        // Cross-platform
        std::make_shared<CrossPlatform::VisualStudioCodeReporter>()};

    for (const auto& reporter : reporters)
    {
        reporter->useCygwinConversions(false);
        reporter->launcher.invokeForWindows(true);
        stream << "windows: " << reporter->getCommandLine("a.txt", "b.txt") << '\n';

        reporter->launcher.invokeForWindows(false);
        stream << "unix   : " << reporter->getCommandLine("a.txt", "b.txt") << '\n';

        reporter->useCygwinConversions(true);
        reporter->launcher.invokeForWindows(false);
        stream << "cygwin : " << reporter->getCommandLine("a.txt", "b.txt") << '\n';
        stream << '\n';
    }
    Approvals::verify(scrubProgramFiles(stream.str()));
}
