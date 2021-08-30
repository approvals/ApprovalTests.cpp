#include "ApprovalTests/writers/StringWriter.h"
#include "EmptyFileCreatorFactory.h"
namespace ApprovalTests
{

    void EmptyFileCreatorFactory::defaultCreator(std::string fullFilePath)
    {
        StringWriter s("", "");
        s.write(fullFilePath);
    }

    EmptyFileCreator EmptyFileCreatorFactory::currentCreator =
        EmptyFileCreatorFactory::defaultCreator;

}
