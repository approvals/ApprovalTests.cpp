#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/namers/HelpMessages.h"
#include "ApprovalTests/namers/FileNameSanitizerFactory.h"
#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <iostream>

namespace ApprovalTests
{
    std::string TestName::directoryPrefix;
    bool TestName::checkBuildConfig_ = true;

    const std::string& TestName::getFileName() const
    {
        checkBuildConfiguration(fileName);
        return fileName;
    }

    std::string TestName::getOriginalFileName()
    {
        return originalFileName;
    }

    void TestName::setFileName(const std::string& file)
    {
        originalFileName = file;
        fileName = file.empty() ? handleBoostQuirks() : findFileName(file);
    }

    std::string TestName::findFileName(const std::string& file)
    {
        auto newFileName = checkParentDirectoriesForFile(file);
        return SystemUtils::checkFilenameCase(newFileName);
    }

    std::string& TestName::rootDirectoryStorage()
    {
        // This method is needed to fix static initialisation order
        static std::string rootDirectory;
        return rootDirectory;
    }

    std::string TestName::checkParentDirectoriesForFile(const std::string& file)
    {
        auto newFileName = directoryPrefix + file;

        if (!FileUtils::fileExists(newFileName))
        {
            // If the build system is Ninja, try looking several levels higher...
            std::string backOne = ".." + SystemUtils::getDirectorySeparator();
            std::string prefix;
            for (int i = 0; i != 10; i++)
            {
                prefix += backOne;
                auto candidateName = prefix + file;
                if (FileUtils::fileExists(candidateName))
                {
                    directoryPrefix = prefix;
                    return candidateName;
                }
            }
        }
        return newFileName;
    }

    bool TestName::registerRootDirectoryFromMainFile(const std::string& file)
    {
        std::cout << "TestName::registerRootDirectoryFromMainFile from __FILE__ " << file
                  << '\n';

        if (file.empty())
        {
            throw std::runtime_error("Cannot register an empty path as root directory");
        }

        std::string adjustedPath = file;
        std::cout << "TestName::registerRootDirectoryFromMainFile found parent  "
                  << adjustedPath << '\n';

        rootDirectoryStorage() = FileUtils::getDirectory(adjustedPath);
        std::cout << "TestName::registerRootDirectoryFromMainFile result        "
                  << rootDirectoryStorage() << '\n';

        return true;
    }

    std::string TestName::getRootDirectory()
    {
        if (!rootDirectoryStorage().empty())
        {
            return rootDirectoryStorage();
        }
        else
        {
            throw std::runtime_error(HelpMessages::getUnconfiguredRootDirectory());
        }
    }

    std::string TestName::handleBoostQuirks() const
    {
        return "";
    }

    void TestName::checkBuildConfiguration(const std::string& fileName)
    {
        if (checkBuildConfig_ && !FileUtils::fileExists(fileName))
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

    std::string ApprovalTestNamer::convertToFileName(const std::string& fileName)
    {
        return FileNameSanitizerFactory::currentSanitizer(fileName);
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

    std::string ApprovalTestNamer::getTestSourceDirectory() const
    {
        auto file = getCurrentTest().getFileName();
        return FileUtils::getDirectory(file);
    }

    std::string ApprovalTestNamer::getRelativeTestSourceDirectory() const
    {
        // We are using the original directory - as obtained from __FILE__,
        // as this seems to be consistent for relative paths, regardless of
        // Ninja __FILE__ quirks
        auto originalDir =
            FileUtils::getDirectory(getCurrentTest().getOriginalFileName());
        originalDir =
            StringUtils::replaceAll(originalDir, TestName::getRootDirectory(), "");
        return originalDir;
    }

    std::string ApprovalTestNamer::getApprovalsSubdirectory() const
    {
        std::string sub_directory;
        if (!testConfiguration().subdirectory.empty())
        {
            sub_directory =
                testConfiguration().subdirectory + SystemUtils::getDirectorySeparator();
        }
        return sub_directory;
    }

    std::string ApprovalTestNamer::getDirectory() const
    {
        std::string directory = getTestSourceDirectory();
        std::string sub_directory = getApprovalsSubdirectory();
        directory += sub_directory;
        SystemUtils::ensureDirectoryExists(directory);
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

    bool ApprovalTestNamer::setCheckBuildConfig(bool enabled)
    {
        auto previous = TestName::checkBuildConfig_;
        TestName::checkBuildConfig_ = enabled;
        return previous;
    }
}
