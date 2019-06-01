#ifndef APPROVALTESTS_CPP_APPROVALTESTNAMER_H
#define APPROVALTESTS_CPP_APPROVALTESTNAMER_H

#include "ApprovalNamer.h"
#include <stack>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "../Macros.h"
#include "../SystemUtils.h"

using std::string;

class TestName {
public:
    const string& getFileName() const {
        return fileName;
    }

    void setFileName(const string &file) {
        fileName = SystemUtils::checkFilenameCase(file);
    }

    std::vector<string> sections;
private:
    string fileName;
};

class TestConfiguration {
public:
    std::string subdirectory;
};

class ApprovalTestNamer : public ApprovalNamer {
private:
public:
    ApprovalTestNamer() {
    }

    std::string getTestName() const {
        std::stringstream ext;
        auto test = getCurrentTest();
        for (size_t i = 0; i < test.sections.size(); i++) {
            if (0 < i) {
                ext << ".";
            }
            ext << test.sections[i];
        }

        return convertToFileName(ext.str());
    }

    static bool isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    static string convertToFileName(const string& fileName)
    {
        std::stringstream result;
        for (auto ch : fileName)
        {
            if (!isForbidden(ch))
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

// <SingleHpp unalterable>
    static TestName &getCurrentTest()
    {
        try
        {
            return currentTest();
        }
        catch( const std::runtime_error& )
        {
            std::string lineBreak = "************************************************************************************\n";
            std::string lineBuffer = "*                                                                                  *\n";
            std::string helpMessage =
                "\n\n" + lineBreak + lineBuffer + 
R"(* Welcome to Approval Tests.
* 
* You have forgotten to configure your test framework for Approval Tests.
* 
* To do this in Catch, add the following to your main.cpp:
* 
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
* 
* To do this in Google Test, add the following to your main.cpp:
* 
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
* 
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/GettingStarted.md
)" +
                    lineBuffer + lineBreak + '\n';
            throw std::runtime_error( helpMessage );
        }
    }
// </SingleHpp>


    // Deprecated - please use getSourceFileName
    string getFileName() {
        return getSourceFileName();
    }


    std::string getSourceFileName() const {
        auto file = getCurrentTest().getFileName();
        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind(".");
        auto fileName = file.substr(start, end - start);
        return convertToFileName(fileName);
    }

    string getDirectory() {
        auto file = getCurrentTest().getFileName();
        auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto directory = file.substr(0, end);
        if ( ! testConfiguration().subdirectory.empty() )
        {
            directory += testConfiguration().subdirectory + SystemUtils::getDirectorySeparator(); 
            SystemUtils::ensureDirectoryExists(directory);
        }
        return directory;
    }

    APPROVAL_TESTS_MACROS_STATIC(TestName, currentTest, NULL)
    APPROVAL_TESTS_MACROS_STATIC(TestConfiguration, testConfiguration, new TestConfiguration)

    virtual string getApprovedFile(string extensionWithDot) {

        return getFullFileName(".approved", extensionWithDot);
    }

    virtual string getReceivedFile(string extensionWithDot) {

        return getFullFileName(".received", extensionWithDot);
    }

    std::string getOutputFileBaseName() const {
        return getSourceFileName() + "." + getTestName();
    }

    std::string getFullFileName(string approved, string extensionWithDot) {
        std::stringstream ext;
        ext << getDirectory() << getOutputFileBaseName() << approved << extensionWithDot;
        return ext.str();
    }
};

#endif
