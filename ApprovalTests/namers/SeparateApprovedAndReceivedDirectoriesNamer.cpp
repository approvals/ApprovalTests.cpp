#include "ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.h"

namespace ApprovalTests
{
    std::string
    SeparateApprovedAndReceivedDirectoriesNamer::getFullFileNameWithExtraDirectory(
        const std::string& approved, const std::string& extensionWithDot) const
    {
        std::string outputDirectory = getDirectory() + approved;
        SystemUtils::ensureDirectoryExists(outputDirectory);

        std::string outputFile = getFileName() + "." + getTestName() + extensionWithDot;

        return outputDirectory + SystemUtils::getDirectorySeparator() + outputFile;
    }

    std::string SeparateApprovedAndReceivedDirectoriesNamer::getApprovedFile(
        std::string extensionWithDot) const
    {
        return getFullFileNameWithExtraDirectory("approved", extensionWithDot);
    }

    std::string SeparateApprovedAndReceivedDirectoriesNamer::getReceivedFile(
        std::string extensionWithDot) const
    {
        return getFullFileNameWithExtraDirectory("received", extensionWithDot);
    }

    DefaultNamerDisposer SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer()
    {
        return Approvals::useAsDefaultNamer([]() {
            return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();
        });
    }
}
