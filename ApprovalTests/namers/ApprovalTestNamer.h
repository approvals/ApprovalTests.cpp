#ifndef APPROVALTESTNAMER_H
#define APPROVALTESTNAMER_H

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

class ApprovalTestNamer {
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

    STATIC(TestName, currentTest, NULL)

    string getApprovedFile(string extentionWithDot) {

        return getFullFileName(".approved", extentionWithDot);
    }

    string getReceivedFile(string extentionWithDot) {

        return getFullFileName(".received", extentionWithDot);
    }

    string getFullFileName(string approved, string extentionWithDot) {
        std::stringstream ext;
        ext << getDirectory() << getFileName() << "." << getTestName() << approved << extentionWithDot;
        return ext.str();
    }
};

#endif
