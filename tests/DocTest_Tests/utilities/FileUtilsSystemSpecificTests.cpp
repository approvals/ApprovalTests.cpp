#include "doctest/doctest.h"
#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/SystemUtils.h"

using namespace ApprovalTests;

TEST_CASE("ItCanCopyAFile")
{
    ApprovalTestNamer namer;
    const auto& sep = SystemUtils::getDirectorySeparator();
    auto source = namer.getDirectory() + ".." + sep + ".." + sep + "sample.txt";
    auto destination = namer.getDirectory() + ".." + sep + "copy.temp.received.txt";

    if (FileUtils::fileExists(destination))
    {
        ::remove(destination.c_str());
    }
    CHECK(!FileUtils::fileExists(destination));
    FileUtilsSystemSpecific::copyFile(source, destination);
    Approvals::verifyExistingFile(destination);
}

TEST_CASE("Test FileUtilsSystemSpecific getCommandLineForCopy")
{
    const std::string source = "source.txt";
    const std::string destination = "destination.txt";

    // Windowsa
    REQUIRE("copy /Y \"source.txt\" \"destination.txt\"" ==
            FileUtilsSystemSpecific::getCommandLineForCopy(source, destination, true));

    // Unix
    REQUIRE("cp \"source.txt\" \"destination.txt\"" ==
            FileUtilsSystemSpecific::getCommandLineForCopy(source, destination, false));
}
