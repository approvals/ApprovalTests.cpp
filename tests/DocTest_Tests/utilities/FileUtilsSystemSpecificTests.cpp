#include "doctest/doctest.h"
#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"

using namespace ApprovalTests;

TEST_CASE("Test FileUtilsSystemSpecific getCommandLineForCopy")
{
    const std::string source = "source.txt";
    const std::string destination = "destination.txt";

    // Windowsa
    REQUIRE("copy /Y \"source.txt\" \"destination.txt\"" ==
            FileUtilsSystemSpecific::getCommandLineForCopy(
                source, destination, true));

    // Unix
    REQUIRE("cp \"source.txt\" \"destination.txt\"" ==
            FileUtilsSystemSpecific::getCommandLineForCopy(
                source, destination, false));
}
