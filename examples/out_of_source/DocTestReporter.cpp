#include "DocTestReporter.h"
#include "ApprovalTests/utilities/FileUtils.h"

#include "doctest/doctest.h"

namespace ApprovalTests
{
    bool DocTestReporter::report(std::string received, std::string approved) const
    {
        auto receivedText = FileUtils::readFileThrowIfMissing(received);
        auto approvedText = FileUtils::readFileThrowIfMissing(approved);
        CHECK(receivedText == approvedText);
        return true;
    }
}
