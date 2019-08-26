#include "Catch.hpp"
#include "ApprovalTests/FileUtilsSystemSpecific.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/SystemUtils.h"
#include "Approvals.h"
#include "FileUtils.h"
#include "FileUtilsSystemSpecific.h"
#include "SystemUtils.h"
#include <stdio.h>

TEST_CASE("ItCanCopyAFile")
{
    ApprovalTestNamer namer;
  const auto& sep = ApprovalTests::SystemUtils::getDirectorySeparator();
  auto source = namer.getDirectory() + ".." + sep + ".." + sep + "sample.txt";
    auto destination = namer.getDirectory() + ".." + sep + "copy.temp.received.txt";

    if ( ApprovalTests::FileUtils::fileExists(destination))
    {
        ::remove(destination.c_str());
    }
    CHECK( ! ApprovalTests::FileUtils::fileExists(destination) );
    ApprovalTests::FileUtilsSystemSpecific::copyFile(source, destination);
    ApprovalTests::Approvals::verifyExistingFile(destination);
}
