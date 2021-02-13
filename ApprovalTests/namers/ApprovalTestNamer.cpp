#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <iostream>

namespace ApprovalTests
{
    std::string TestName::directoryPrefix;

    const std::string& TestName::getFileName() const
    {
        checkBuildConfiguration(fileName);
        return fileName;
    }

    void TestName::setFileName(const std::string& file)
    {
        fileName = directoryPrefix + file;
        if (!FileUtils::fileExists(fileName))
        {
            // If the build system is Ninja, try looking several levels higher...

            // clang-format off
            std::vector<std::string> alternativePrefixes{
                "../",
                "../../",
                "../../../",
                "../../../../",
                "../../../../../",
            };
            // clang-format on
            for (const auto& prefix : alternativePrefixes)
            {
                const auto candidateName = prefix + file;
                if (FileUtils::fileExists(candidateName))
                {
                    fileName = candidateName;
                    directoryPrefix = prefix;
                    break;
                }
            }
        }
        fileName = SystemUtils::checkFilenameCase(fileName);
    }

    void TestName::checkBuildConfiguration(const std::string& fileName)
    {
        if (!FileUtils::fileExists(fileName))
        {
            throw std::runtime_error(getMisconfiguredBuildHelp(fileName));
        }
    }

    std::string TestName::getMisconfiguredBuildHelp(const std::string& fileName)
    {
        return "\n\n" + HelpMessages::getMisconfiguredBuildHelp(fileName) + "\n\n";
    }

    std::string ApprovalTestNamer::getTestName() const
    {
        std::stringstream ext;
        auto test = getCurrentTest();
        for (size_t i = 0; i < test.sections.size(); i++)
        {
            if (0 < i)
            {
                ext << ".";
            }
            ext << test.sections[i];
        }

        return convertToFileName(ext.str());
    }

    bool ApprovalTestNamer::isForbidden(char c)
    {
        static std::string forbiddenChars("\\/:?\"<>|' ");
        return std::string::npos != forbiddenChars.find(c);
    }

    std::string ApprovalTestNamer::convertToFileName(const std::string& fileName)
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

    TestName& ApprovalTestNamer::getCurrentTest()
    {
        try
        {
            return currentTest();
        }
        catch (const std::runtime_error&)
        {
            std::string helpMessage = getMisconfiguredMainHelp();
            throw std::runtime_error(helpMessage);
        }
    }

    std::string ApprovalTestNamer::getMisconfiguredMainHelp()
    {
        return "\n\n" + HelpMessages::getMisconfiguredMainHelp() + "\n\n";
    }

    std::string ApprovalTestNamer::getFileName() const
    {
        return getSourceFileName();
    }

    std::string ApprovalTestNamer::getSourceFileName() const
    {
        auto file = getCurrentTest().getFileName();
        auto start = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto end = file.rfind('.');
        auto fileName = file.substr(start, end - start);
        return convertToFileName(fileName);
    }

    std::string ApprovalTestNamer::getDirectory() const
    {
        auto file = getCurrentTest().getFileName();
        auto end = file.rfind(SystemUtils::getDirectorySeparator()) + 1;
        auto directory = file.substr(0, end);
        if (!testConfiguration().subdirectory.empty())
        {
            directory +=
                testConfiguration().subdirectory + SystemUtils::getDirectorySeparator();
            SystemUtils::ensureDirectoryExists(directory);
        }
        return directory;
    }

    TestName& ApprovalTestNamer::currentTest(TestName* value)
    {
        static TestName* staticValue;
        if (value != nullptr)
        {
            staticValue = value;
        }
        if (staticValue == nullptr)
        {
            throw std::runtime_error("The variable in currentTest() is not initialised");
        }
        return *staticValue;
    }

    TestConfiguration& ApprovalTestNamer::testConfiguration()
    {
        static TestConfiguration configuration;
        return configuration;
    }

    std::string ApprovalTestNamer::getApprovedFile(std::string extensionWithDot) const
    {

        return getFullFileName(".approved", extensionWithDot);
    }

    std::string ApprovalTestNamer::getReceivedFile(std::string extensionWithDot) const
    {

        return getFullFileName(".received", extensionWithDot);
    }

    std::string ApprovalTestNamer::getOutputFileBaseName() const
    {
        return getSourceFileName() + "." + getTestName();
    }

    std::string
    ApprovalTestNamer::getFullFileName(const std::string& approved,
                                       const std::string& extensionWithDot) const
    {
        std::stringstream ext;
        ext << getDirectory() << getOutputFileBaseName() << approved << extensionWithDot;
        return ext.str();
    }
}
