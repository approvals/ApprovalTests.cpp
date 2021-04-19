#include "ApprovalTests/writers/ExistingFile.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    std::string ExistingFile::scrub(std::string fileName, const Options& options)
    {
        if (options.isUsingDefaultScrubber())
        {
            return fileName;
        }
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

    ExistingFile::ExistingFile(std::string filePath_, const Options& options)
        : options_(options)
    {
        filePath = scrub(filePath_, options);
    }

    std::string ExistingFile::getFileExtensionWithDot() const
    {
        return FileUtils::getExtensionWithDot(filePath);
    }

    void ExistingFile::write(std::string) const
    {
        // do nothing
    }

    void ExistingFile::cleanUpReceived(std::string receivedPath) const
    {
        if (deleteScrubbedFile && (receivedPath == filePath))
        {
            remove(receivedPath.c_str());
        }
    }

    ExistingFileNamer ExistingFile::getNamer()
    {
        return ExistingFileNamer(filePath, options_);
    }
}
