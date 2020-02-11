#include "catch2/catch.hpp"

#include "ApprovalTests/utilities/SystemUtils.h"
#include "ApprovalTests/Approvals.h"
#include "ApprovalTests/utilities/MachineBlocker.h"

// Can't move this to DocTests tests as it gives this compilation error:
// In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/wchar.h:90,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/cwchar:44,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/bits/postypes.h:40,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/bits/char_traits.h:40,
//                  from /usr/local/Cellar/gcc/9.2.0_2/include/c++/9.2.0/string:40,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/FileUtils.h:8,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/SystemUtils.h:16,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/tests/Catch2_Tests/utilities/MachineBlockerTests.cpp:3:
// /usr/local/Cellar/gcc/9.2.0_2/lib/gcc/9/gcc/x86_64-apple-darwin18/9.2.0/include-fixed/stdio.h:222:7: error: conflicting declaration of 'char* ctermid(char*)' with 'C' linkage
//   222 | char *ctermid(char *);
//       |       ^~~~~~~
// In file included from /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/unistd.h:525,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/ApprovalTests/../ApprovalTests/utilities/SystemUtils.h:12,
//                  from /Users/clare/Documents/develop/ApprovalTests/ApprovalTests.cpp/tests/Catch2_Tests/utilities/MachineBlockerTests.cpp:3:
// /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/_ctermid.h:26:10: note: previous declaration with 'C++' linkage
//    26 | char    *ctermid(char *);
//       |          ^~~~~~~

using namespace ApprovalTests;

TEST_CASE("Blocks in this environment")
{
    auto machineName = SystemUtils::getMachineName();
    auto blocker = MachineBlocker::onMachineNamed(machineName);
    REQUIRE(blocker.isBlockingOnThisMachine() == true);
}

TEST_CASE("Does not block in this environment")
{
    auto machineName = SystemUtils::getMachineName();
    auto blocker = MachineBlocker::onMachinesNotNamed(machineName);
    REQUIRE(blocker.isBlockingOnThisMachine() == false);
}

// begin-snippet: machine_specific_test_runner
TEST_CASE("Only run this test on John's machine")
{
    auto blocker = MachineBlocker::onMachinesNotNamed("JOHNS_MACHINE");
    if (blocker.isBlockingOnThisMachine())
    {
        return;
    }
    // Write tests here that depend on John's environment.
    REQUIRE(SystemUtils::getMachineName() == "JOHNS_MACHINE");
}
// end-snippet
