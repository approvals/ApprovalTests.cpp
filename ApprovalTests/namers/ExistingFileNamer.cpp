#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "DefaultNamerFactory.h"

namespace ApprovalTests
{
    ExistingFileNamer::ExistingFileNamer(std::string filePath_)
        : filePath(std::move(filePath_))
    {
    }

    std::string ExistingFileNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return DefaultNamerFactory::getDefaultNamer()()->getApprovedFile(
            extensionWithDot);
    }

    std::string ExistingFileNamer::getReceivedFile(std::string) const
    {
        return filePath;
    }
}
