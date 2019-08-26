#include "Catch.hpp"
#include "ApprovalTests/FileUtilsSystemSpecific.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/SystemUtils.h"
#include "Approvals.h"
#include <stdio.h>

TEST_CASE("ItCanCopyAFile")
{
    ApprovalTestNamer namer;
  const auto& sep = SystemUtils::getDirectorySeparator();
  auto source = namer.getDirectory() + ".." + sep + ".." + sep + "sample.txt";
    auto destination = namer.getDirectory() + ".." + sep + "copy.temp.received.txt";

    if ( FileUtils::fileExists(destination))
    {
        ::remove(destination.c_str());
    }
    CHECK( ! FileUtils::fileExists(destination) );
    FileUtilsSystemSpecific::copyFile(source, destination);
    ApprovalTests::Approvals::verifyExistingFile(destination);
}
