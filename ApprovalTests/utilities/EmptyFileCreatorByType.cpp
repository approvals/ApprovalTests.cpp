#include "EmptyFileCreatorByType.h"
#include "ApprovalTests/writers/StringWriter.h"
#include "StringUtils.h"

namespace
{
    std::map<std::string, ApprovalTests::EmptyFileCreator>
    defaultEmptyFileCreatorByTypeCreators()
    {
        std::map<std::string, ApprovalTests::EmptyFileCreator> creators;
        ApprovalTests::EmptyFileCreator wibbleCreator = [](std::string fileName) {
            ApprovalTests::StringWriter s("{}");
            s.write(fileName);
        };
        creators[".json"] = wibbleCreator;
        return creators;
    }
}

namespace ApprovalTests
{
    std::map<std::string, ApprovalTests::EmptyFileCreator>
        EmptyFileCreatorByType::creators_ = defaultEmptyFileCreatorByTypeCreators();

    void EmptyFileCreatorByType::registerCreator(const std::string& extensionWithDot,
                                                 EmptyFileCreator creator)
    {
        creators_[extensionWithDot] = std::move(creator);
    }

    void EmptyFileCreatorByType::createFile(const std::string& fileName)
    {
        for (const auto& creator : creators_)
        {
            if (StringUtils::endsWith(fileName, creator.first))
            {
                creator.second(fileName);
                return;
            }
        }
        EmptyFileCreatorFactory::defaultCreator(fileName);
    }
}
