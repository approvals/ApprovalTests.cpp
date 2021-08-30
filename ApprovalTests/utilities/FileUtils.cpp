#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "EmptyFileCreatorFactory.h"
#include "EmptyFileCreatorDisposer.h"
#include "SystemUtils.h"

#include <fstream>
#include <sys/stat.h>
#include <sstream>

namespace ApprovalTests
{
    bool FileUtils::fileExists(const std::string& path)
    {
        struct stat info
        {
        };
        return stat(path.c_str(), &info) == 0;
    }

    int FileUtils::fileSize(const std::string& path)
    {
        struct stat statbuf
        {
        };
        int stat_ok = stat(path.c_str(), &statbuf);

        if (stat_ok == -1)
        {
            return -1;
        }

        return int(statbuf.st_size);
    }

    EmptyFileCreatorDisposer FileUtils::useEmptyFileCreator(EmptyFileCreator creator)
    {
        return EmptyFileCreatorDisposer(creator);
    }

    void FileUtils::ensureFileExists(const std::string& fullFilePath)
    {
        if (!fileExists(fullFilePath))
        {
            EmptyFileCreatorFactory::currentCreator(fullFilePath);
        }
    }

    std::string FileUtils::getDirectory(const std::string& filePath)
    {
        auto end = filePath.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto directory = filePath.substr(0, end);
        return directory;
    }

    std::string FileUtils::getExtensionWithDot(const std::string& filePath)
    {
        std::size_t found = filePath.find_last_of('.');
        return filePath.substr(found);
    }

    std::string FileUtils::readFileThrowIfMissing(const std::string& fileName)
    {
        std::ifstream in(fileName.c_str(), std::ios_base::in);
        if (!in)
        {
            throw std::runtime_error("File does not exist: " + fileName);
        }
        std::stringstream written;
        written << in.rdbuf();
        in.close();

        std::string text = written.str();
        return text;
    }

    std::string FileUtils::readFileReturnEmptyIfMissing(const std::string& fileName)
    {
        if (FileUtils::fileExists(fileName))
        {
            return readFileThrowIfMissing(fileName);
        }
        else
        {
            return std::string();
        }
    }

    void FileUtils::writeToFile(const std::string& filePath, const std::string& content)
    {
        std::ofstream out(filePath.c_str(), std::ios::binary | std::ofstream::out);
        if (!out)
        {
            throw std::runtime_error("Unable to write file: " + filePath);
        }
        out << content;
    }

}
