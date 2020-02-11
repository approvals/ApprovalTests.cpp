#include "catch2/catch.hpp"
#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"
#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/SystemUtils.h"
#include <stdio.h>

// Can't move this to DocTests tests as it gives this compilation error:
// In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/wchar.h:90,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/cwchar:44,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/bits/postypes.h:40,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/bits/char_traits.h:40,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/string:40,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/FileUtils.h:8,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/SystemUtils.h:16,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/FileUtilsSystemSpecific.h:4,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/tests/Catch2_Tests/utilities/FileUtilsSystemSpecificTests.cpp:2:
// /usr/local/Cellar/gcc/9.2.0_2/lib/gcc/9/gcc/x86_64-apple-darwin18/9.2.0/include-fixed/stdio.h:222:7: error: conflicting declaration of 'char* ctermid(char*)' with 'C' linkage
//   222 | char *ctermid(char *);
//       |       ^~~~~~~
// In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/unistd.h:525,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/SystemUtils.h:12,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/FileUtilsSystemSpecific.h:4,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/tests/Catch2_Tests/utilities/FileUtilsSystemSpecificTests.cpp:2:
// /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/_ctermid.h:26:10: note: previous declaration with 'C++' linkage
//    26 | char    *ctermid(char *);
//       |          ^~~~~~~
//

using namespace ApprovalTests;

TEST_CASE("ItCanCopyAFile")
{
    ApprovalTestNamer namer;
    const auto& sep = SystemUtils::getDirectorySeparator();
    auto source = namer.getDirectory() + ".." + sep + ".." + sep + "sample.txt";
    auto destination =
        namer.getDirectory() + ".." + sep + "copy.temp.received.txt";

    if (FileUtils::fileExists(destination))
    {
        ::remove(destination.c_str());
    }
    CHECK(!FileUtils::fileExists(destination));
    FileUtilsSystemSpecific::copyFile(source, destination);
    Approvals::verifyExistingFile(destination);
}