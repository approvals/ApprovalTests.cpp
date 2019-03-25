//
// Created by LLEWELLYN FALCO on 12/2/17.
//

#ifndef APPROVALTESTS_CPP_FILEUTILS_H
#define APPROVALTESTS_CPP_FILEUTILS_H

#include <string>
#include <sys/stat.h>
#include "StringWriter.h"
#include <sys/types.h>

class FileUtils {
public:
    static bool fileExists(std::string path)
    {
        struct stat info;
        return stat( path.c_str(), &info ) == 0;
    }

    static int fileSize(std::string path) {
        struct stat statbuf;
        int stat_ok = stat(path.c_str(), &statbuf);

        if (stat_ok == -1) {
            return -1;
        }

        return int(statbuf.st_size);
    }

    static void ensureFileExists(std::string fullFilePath) {
        if (!fileExists(fullFilePath)) {
            StringWriter s("", "");
            s.write(fullFilePath);
        }
    }

    static std::string getExtensionWithDot(std::string filePath) {
        std::size_t found = filePath.find_last_of(".");
        return filePath.substr(found);
    }

    static void writeToFile(std::string filePath, std::string content)
    {
        std::ofstream out(filePath.c_str(), std::ios::binary | std::ofstream::out);
        out << content;
    }
};

#endif // APPROVALTESTS_CPP_FILEUTILS_H
