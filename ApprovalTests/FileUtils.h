//
// Created by LLEWELLYN FALCO on 12/2/17.
//

#ifndef CATCHPLAYGROUND_FILEUTILS_H
#define CATCHPLAYGROUND_FILEUTILS_H

#include <string>
#include <sys/stat.h>
#include "StringWriter.h"

class FileUtils {
public:
    static bool fileExists(std::string path) {
        return fileSize(path) != -1;
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
            s.Write(fullFilePath);
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

#endif //CATCHPLAYGROUND_FILEUTILS_H
