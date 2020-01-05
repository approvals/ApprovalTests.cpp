#ifndef APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
#define APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H

#ifdef _MSC_VER
static_assert(__FILE__[1] == ':',
              "Please compile with /FC, see <link> for details");
#else
static_assert(__FILE__[0] == '/',
              R"(
********************************************************************************
* Welcome to Approval Tests.
*
* There seems to be a problem with your build configuration:
* we cannot find the test source file.
*
* ApprovalTests requires an absolute path to source file locations - not the
* relative one given by this build.
*
* A common cause of this problem is using Ninja with in-tree builds.
*
* For details on how to fix this, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md
********************************************************************************
)");
#endif

#endif //APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
