#include "Catch.hpp"
#include "ApprovalTests/FileUtilsSystemSpecific.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include <stdio.h>

TEST_CASE("ItCanCopyAFile")
{
    ApprovalTestNamer namer;
    auto source = namer.getDirectory() + "../sample.txt";
    auto destination = namer.getDirectory() + "../copy.temp.received.txt";

    if ( FileUtils::fileExists(destination))
    {
        ::remove(destination.c_str());
    }
    CHECK( ! FileUtils::fileExists(destination) );
    FileUtilsSystemSpecific::copyFile(source, destination);
    Approvals::verifyExistingFile(destination);
}
