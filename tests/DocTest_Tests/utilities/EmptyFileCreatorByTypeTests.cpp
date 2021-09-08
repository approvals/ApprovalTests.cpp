#include "utilities/EmptyFileCreatorByType.h"
#include "doctest/doctest.h"
#include "utilities/FileUtils.h"
#include "utilities/EmptyFileCreatorFactory.h"
#include "Approvals.h"

using namespace ApprovalTests;

TEST_CASE("Test register customization")
{
    EmptyFileCreator wibbleCreator = [](std::string fileName)
    {
        StringWriter s("Wobble");
        s.write(fileName);
    };
    EmptyFileCreatorByType::registerCreator(".wibble", wibbleCreator);

    auto received = Approvals::getDefaultNamer()->getReceivedFile(".wibble");
    remove(received.c_str());

    FileUtils::ensureFileExists(received);
    REQUIRE("Wobble\n" == FileUtils::readFileThrowIfMissing(received));
}
