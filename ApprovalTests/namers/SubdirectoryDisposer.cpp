#include "ApprovalTests/namers/SubdirectoryDisposer.h"
#include "ApprovalTestNamer.h"

namespace ApprovalTests
{
    SubdirectoryDisposer::SubdirectoryDisposer(std::string subdirectory)
    {
        previous_result = ApprovalTestNamer::testConfiguration().subdirectory;
        ApprovalTestNamer::testConfiguration().subdirectory = std::move(subdirectory);
    }

    SubdirectoryDisposer::~SubdirectoryDisposer()
    {
        ApprovalTestNamer::testConfiguration().subdirectory = previous_result;
    }
}
