#ifndef APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
#define APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H

// Maintenance note: the following help message must be short, and
// not contain any newline characters, as their display looks messy
// in some compiler outputs.

#ifdef _WIN32
static_assert(__FILE__[1] == ':',
#else
static_assert(__FILE__[0] == '/',
#endif
              // clang-format off
"There seems to be a problem with your build configuration, probably with Ninja. "
"Please visit https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md"
              // clang-format on
);

#endif //APPROVALTESTS_CPP_CHECKFILEMACROISABSOLUTE_H
