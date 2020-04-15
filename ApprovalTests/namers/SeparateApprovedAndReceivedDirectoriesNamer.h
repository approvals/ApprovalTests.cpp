#pragma once

#include "ApprovalTestNamer.h"
#include "../Approvals.h"

namespace ApprovalTests
{
    class SeparateApprovedAndReceivedDirectoriesNamer : public ApprovalTestNamer
    {
    public:
        virtual ~SeparateApprovedAndReceivedDirectoriesNamer() override = default;

        std::string
        getFullFileNameWithExtraDirectory(const std::string& approved,
                                          const std::string& extensionWithDot) const
        {
            std::string outputDirectory = getDirectory() + approved;
            SystemUtils::ensureDirectoryExists(outputDirectory);

            std::string outputFile =
                getFileName() + "." + getTestName() + extensionWithDot;

            return outputDirectory + SystemUtils::getDirectorySeparator() + outputFile;
        }

        virtual std::string getApprovedFile(std::string extensionWithDot) const override
        {
            return getFullFileNameWithExtraDirectory("approved", extensionWithDot);
        }

        virtual std::string getReceivedFile(std::string extensionWithDot) const override
        {
            return getFullFileNameWithExtraDirectory("received", extensionWithDot);
        }

        static DefaultNamerDisposer useAsDefaultNamer()
        {
            return Approvals::useAsDefaultNamer([]() {
                return std::make_shared<SeparateApprovedAndReceivedDirectoriesNamer>();
            });
        }
    };
}
