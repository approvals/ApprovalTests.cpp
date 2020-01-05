#ifndef APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
#define APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H

#ifdef _MSC_VER
static_assert(__FILE__[1] == ':',
              "Please compile with /FC, see <link> for details");
#else
static_assert(__FILE__[0] == '/',
              "\nApprovalTests requires an absolute path to source file "
              "locations - not the relative one given by this build.\n"
              "A common cause of this problem is using Ninja with in-tree "
              "builds.\n"
              "Please see "
              "https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/"
              "TroubleshootingMisconfiguredBuild.md#top\n"
              "for help.\n\n");
#endif

#endif //APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
