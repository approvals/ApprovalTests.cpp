#include "utilities/EmptyFileCreatorByType.h"
#include "doctest/doctest.h"
#include "utilities/FileUtils.h"
#include "utilities/EmptyFileCreatorFactory.h"
#include "Approvals.h"

using namespace ApprovalTests;

namespace
{
    void assertNewFileContents(const std::string& extensionWithDot,
                               const std::string& expectedContents)
    {
        auto received = Approvals::getDefaultNamer()->getReceivedFile(extensionWithDot);
        remove(received.c_str());

        FileUtils::ensureFileExists(received);
        CHECK(expectedContents + "\n" == FileUtils::readFileThrowIfMissing(received));
    }
}

TEST_CASE("Test register customization")
{
    EmptyFileCreator wibbleCreator = [](std::string fileName) {
        StringWriter s("Wobble");
        s.write(fileName);
    };
    EmptyFileCreatorByType::registerCreator(".wibble", wibbleCreator);
    assertNewFileContents(".wibble", "Wobble");
}

TEST_CASE("Test default contents of new files by type")
{
    assertNewFileContents(".json", "{}");
}
