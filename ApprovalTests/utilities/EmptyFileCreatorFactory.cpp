#include "ApprovalTests/writers/StringWriter.h"
#include "EmptyFileCreatorFactory.h"
#include "EmptyFileCreatorByType.h"
namespace ApprovalTests
{

    void EmptyFileCreatorFactory::defaultCreator(std::string fullFilePath)
    {
        StringWriter s("", "");
        s.write(fullFilePath);
    }

    EmptyFileCreator EmptyFileCreatorFactory::currentCreator =
        EmptyFileCreatorByType::createFile;
}
