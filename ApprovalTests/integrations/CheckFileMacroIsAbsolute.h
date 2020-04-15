#pragma once

// Maintenance note: the following help message must be short, and
// not contain any newline characters, as their display looks messy
// in some compiler outputs.
//
// This static_assert can be disabled by
// defining APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK.
// This can be done on the CMake command line with:
// -DCMAKE_CXX_FLAGS_INIT=-DAPPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK
//
// ApprovalTests will then check the validity of __FILE__
// at run-time instead, for test frameworks that use it to
// detect the source file name.
#ifndef APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK
// clang-format off
static_assert(
    (__FILE__[1] == ':') ||
    (__FILE__[0] == '/'),
              // begin-snippet: compiler_error_for_misconfigured_build
"There seems to be a problem with your build configuration, probably with Ninja. "
"Please visit https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredBuild.md "
"The filename is: "
__FILE__
              // end-snippet
    // clang-format on
);
#endif // APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK
