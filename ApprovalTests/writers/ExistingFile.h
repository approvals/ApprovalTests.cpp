#pragma once

#include <utility>
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "ApprovalTests/core/ApprovalWriter.h"

namespace ApprovalTests
{
    class ExistingFile : public ApprovalWriter
    {
        std::string filePath;
        bool deleteScrubbedFile = false;
        const Options& options_;

        std::string scrub(std::string fileName, const Options& options);

    public:
        explicit ExistingFile(std::string filePath_, const Options& options);
        virtual std::string getFileExtensionWithDot() const override;
        virtual void write(std::string /*path*/) const override;
        virtual void cleanUpReceived(std::string receivedPath) const override;
        ExistingFileNamer getNamer();
    };
}
