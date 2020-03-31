See the [v.7.0.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/2?closed=1) for the full list of changes.

* **Breaking changes**
    * If you are using Catch, we have changed the casing of the file that Approval Tests looks for, to be consistent with Catch downloads (#53). If you get build failures, you'll need to change your `#include` lines like this:
        ```diff
        -#include "Catch.hpp"
        +#include "catch.hpp"
        ```
    * If you pass in a reporter to `CombinationApprovals::verifyAllCombinations()`, the argument order has changed, and is now the first argument: see [Passing in a Reporter](/doc/TestingCombinations.md#passing-in-a-reporter). (#47 - thanks to @mika-fischer, Mika Fischer)
* **New features**
    * Support for the [\[Boost\].UT test framework](https://github.com/boost-experimental/ut). See [Using Approval Tests With \[Boost\].UT](/doc/UsingUT.md#top). (#58 - thanks to @lp55, Luiz Paulo M. Pires and @krzysztof-jusiak, Kris Jusiak)
    * Support for differencing tools in Tortoise Git. (#57 - thanks to @lp55, Luiz Paulo M. Pires)
* **Bug fixes**
    * Fixed tests failing when using Ninja generator used by Visual Studio 2019 (#55).
        * See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top) if you have test failures in your VS2019 builds.
    * Fixed unnecessary duplicate static functions. (#54)
    * Fixed `ClipboardReporter` on macOS. (#51)
    * ~~Fixed inability to use project as sub-module on windows due to long filenames - by shortening the names of some files and folders in the tests. (#38)~~
* **Other changes**
    * Documentation improvements (Thanks to Neil Horlock)
    * Updated our copy of Catch to v2.11.0 (from v2.7.1)
    * Added GitHub actions (#31 - thanks @alastairUK)
