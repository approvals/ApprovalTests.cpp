#pragma once

#include <string>
#include <utility>
#include <fstream>
#include "ApprovalTests/core/Options.h"
#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "ApprovalTests/core/ApprovalWriter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    class ExistingFile : public ApprovalWriter
    {
        std::string filePath;
        bool deleteScrubbedFile = false;

        std::string scrub(std::string fileName, const Options& options)
        {
            auto content = FileUtils::readFileThrowIfMissing(fileName);
            const auto scrubbedContent = options.scrub(content);
            if (content == scrubbedContent)
            {
                deleteScrubbedFile = false;
                return fileName;
            }
            else
            {
                std::size_t found = fileName.find_last_of('.');
                auto fileExtension = fileName.substr(found);
                std::string baseName = fileName.substr(0, found);

                auto newFileName = baseName + ".scrubbed.received" + fileExtension;
                FileUtils::writeToFile(newFileName, scrubbedContent);
                deleteScrubbedFile = true;
                return newFileName;
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
        virtual void cleanUpReceived(std::string receivedPath) const override
        {
            if (deleteScrubbedFile && (receivedPath == filePath))
            {
                remove(receivedPath.c_str());
            }
        }
        ExistingFileNamer getNamer()
        {
            return ExistingFileNamer(filePath);
        }
    };
}
