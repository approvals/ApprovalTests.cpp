#ifndef APPROVALTESTS_CPP_APPROVALTESTNAMER_H
#define APPROVALTESTS_CPP_APPROVALTESTNAMER_H

#include "ApprovalTests/core/ApprovalNamer.h"
#include <stack>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "ApprovalTests/utilities/SystemUtils.h"

namespace ApprovalTests {
class TestName {
public:
    const std::string& getFileName() const {
        checkBuildConfiguration();
        return fileName;
    }

    void setFileName(const std::string &file) {
        fileName = SystemUtils::checkFilenameCase(file);
    }

    std::vector<std::string> sections;
private:
    void checkBuildConfiguration() const {
        if(! FileUtils::fileExists(fileName))
        {
            throw std::runtime_error("File " + fileName + " does not exist - check your compiler args");
        }
    }

    std::string fileName;
};

class TestConfiguration {
public:
    std::string subdirectory;
};

class ApprovalTestNamer : public ApprovalNamer {
private:
public:
    ApprovalTestNamer() = default;

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

    static std::string convertToFileName(const std::string& fileName)
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

    static TestName &getCurrentTest()
    {
        try
        {
            return currentTest();
        }
        catch( const std::runtime_error& )
        {
            std::string helpMessage = getMisconfiguredMainHelp();
            throw std::runtime_error( helpMessage );
        }
    }

// <SingleHpp unalterable>
    static std::string getMisconfiguredMainHelp()
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
* To do this in doctest, add the following to your main.cpp:
*
*     #define APPROVALS_DOCTEST
*     #include "ApprovalTests.hpp"
*
* To do this in [Boost].UT, add the following to your main.cpp:
*
*     #define APPROVALS_UT
*     #include "ApprovalTests.hpp"
*
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/GettingStarted.md
)" +
                    lineBuffer + lineBreak + '\n';
        return helpMessage;
    }
// </SingleHpp>


    // Deprecated - please use getSourceFileName
    std::string getFileName() const {
        return getSourceFileName();
    }


    std::string getSourceFileName() const {
        auto file = getCurrentTest().getFileName();
        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind('.');
        auto fileName = file.substr(start, end - start);
        return convertToFileName(fileName);
    }

    std::string getDirectory() const {
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

    static TestName& currentTest(TestName* value = nullptr)
    {
        static TestName* staticValue;
        if (value != nullptr)
        {
            staticValue = value;
        }
        if ( staticValue == nullptr )
        {
            throw std::runtime_error("The variable in currentTest() is not initialised");
        }
        return *staticValue;
    }

    static TestConfiguration& testConfiguration()
    {
        static TestConfiguration configuration;
        return configuration;
    }

    virtual std::string getApprovedFile(std::string extensionWithDot) const override {

        return getFullFileName(".approved", extensionWithDot);
    }

    virtual std::string getReceivedFile(std::string extensionWithDot) const override {

        return getFullFileName(".received", extensionWithDot);
    }

    std::string getOutputFileBaseName() const {
        return getSourceFileName() + "." + getTestName();
    }

    std::string getFullFileName(const std::string& approved, const std::string& extensionWithDot) const {
        std::stringstream ext;
        ext << getDirectory() << getOutputFileBaseName() << approved << extensionWithDot;
        return ext.str();
    }
};
}

#endif
