#ifndef APPROVALTESTNAMER_H
#define APPROVALTESTNAMER_H

#include "ApprovalNamer.h"
#include <stack>
#include <sstream>
#include <vector>
#include "../Macros.h"
#include "../SystemUtils.h"

using std::string;

class TestName {
public:
    string fileName;
    std::vector<string> sections;
};

class ApprovalTestNamer : public ApprovalNamer {
private:
public:
    ApprovalTestNamer() {
    }

    string getTestName() {
        std::stringstream ext;
        auto test = currentTest();
        for (size_t i = 0; i < test.sections.size(); i++) {
            if (0 < i) {
                ext << ".";
            }
            ext << test.sections[i];
        }

        return ext.str();
    }

    string getFileName() {
        auto file = SystemUtils::checkFilenameCase(currentTest().fileName);

        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind(".");
        return file.substr(start, end - start);
    }

    string getDirectory() {
        auto file = currentTest().fileName;
        auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        return file.substr(0, end);
    }

    static bool isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    static string convertToFileName(const string& fileName)
    {
        std::stringstream result;
        for(auto ch : fileName)
        {
            if(!isForbidden(ch))
            {
                result << ch;
            }
            else
            {
                result << "_";
            }
        }
        return result.str();
    }

    STATIC(TestName, currentTest, NULL)

    virtual string getApprovedFile(string extentionWithDot) {

        return getFullFileName(".approved", extentionWithDot);
    }

    virtual string getReceivedFile(string extentionWithDot) {

        return getFullFileName(".received", extentionWithDot);
    }

    string getFullFileName(string approved, string extentionWithDot) {
        std::stringstream ext;
        ext << getDirectory() << getFileName() << "." << getTestName() << approved << extentionWithDot;
        return ext.str();
    }
};

#endif
