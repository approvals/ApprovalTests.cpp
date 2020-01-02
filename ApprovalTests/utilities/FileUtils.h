//
// Created by LLEWELLYN FALCO on 12/2/17.
//

#ifndef APPROVALTESTS_CPP_FILEUTILS_H
#define APPROVALTESTS_CPP_FILEUTILS_H

#include <string>
#include <sys/stat.h>
#include "ApprovalTests/writers/StringWriter.h"

namespace ApprovalTests
{
    class FileUtils
    {
    public:
        static bool fileExists(const std::string& path)
        {
            struct stat info
            {
            };
            return stat(path.c_str(), &info) == 0;
        }

        static int fileSize(const std::string& path)
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

        static void ensureFileExists(const std::string& fullFilePath)
        {
            if (!fileExists(fullFilePath))
            {
                StringWriter s("", "");
                s.write(fullFilePath);
            }
        }

        static std::string getExtensionWithDot(const std::string& filePath)
        {
            std::size_t found = filePath.find_last_of('.');
            return filePath.substr(found);
        }

        static void writeToFile(const std::string& filePath,
                                const std::string& content)
        {
            std::ofstream out(filePath.c_str(),
                              std::ios::binary | std::ofstream::out);
            if (!out)
            {
                throw std::runtime_error("Unable to write file: " + filePath);
            }
            out << content;
        }
    };
}

#endif //APPROVALTESTS_CPP_FILEUTILS_H
