#include "ApprovalTests/namers/ExistingFileNamer.h"
#include "DefaultNamerFactory.h"

namespace ApprovalTests
{
    ExistingFileNamer::ExistingFileNamer(std::string filePath_, const Options& options)
        : filePath(std::move(filePath_)), options_(options)
    {
    }

    ExistingFileNamer::ExistingFileNamer(const ExistingFileNamer& x)
        : filePath(x.filePath), options_(x.options_)
    {
    }

    ExistingFileNamer::ExistingFileNamer(ExistingFileNamer&& x) noexcept
        : filePath(std::move(x.filePath)), options_(x.options_)
    {
    }

    std::string ExistingFileNamer::getApprovedFile(std::string extensionWithDot) const
    {
        return options_.getNamer()->getApprovedFile(extensionWithDot);
    }

    std::string ExistingFileNamer::getReceivedFile(std::string) const
    {
        return filePath;
    }
}
