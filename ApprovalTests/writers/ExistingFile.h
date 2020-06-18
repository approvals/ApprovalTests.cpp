#pragma once

#include <string>
#include <utility>
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "ApprovalTests/core/ApprovalWriter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    class ExistingFile : public ApprovalWriter
    {
        std::string filePath;

        std::string scrub(std::string fileName, const Options& options)
        {
            auto content = FileUtils::readFileThrowIfMissing(fileName);
            if (content == options.scrub(content))
            {
                return fileName;
            }
            else
            {
                throw std::runtime_error("Scrubbers not handled yet");
            }
        }

    public:
        explicit ExistingFile(std::string filePath_, const Options& options)
        {
            filePath = scrub(filePath_, options);
        }
        virtual std::string getFileExtensionWithDot() const override
        {
            return FileUtils::getExtensionWithDot(filePath);
        }
        virtual void write(std::string /*path*/) const override
        {
            // do nothing
        }
        virtual void cleanUpReceived(std::string /*receivedPath*/) const override
        {
            // do nothing
        }
        ExistingFileNamer getNamer()
        {
            return ExistingFileNamer(filePath);
        }
    };
}
