See the [v.8.0.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/4?closed=1) for the full list of changes.

* **Breaking changes**
    * We have fully standardised the way that Approval Tests looks for 3rd-party headers, so users should no longer need to modify their search paths for include directories. This means that:
    * If you are using Catch (#62), and you get build failures, you'll need to change your `#include` lines like this:
        ```diff
        -#include <catch.hpp>
        +#include <catch2/catch.hpp>
        ```
    * If you are using doctest (#68), and you get build failures, you'll need to change your `#include` lines like this:
        ```diff
        -#include <doctest.h>
        +#include <doctest/doctest.h>
        ```
    * If you are using \[Boost\].UT (#65), and you get build failures, you'll need to change your `#include` lines like this:
        ```diff
        -#include <ut.hpp>
        +#include <boost/ut.hpp>
        ```
    * In order for this to work with our third_party directory, our copies of these header files are now in:
        * `third_party/catch2/include/catch2/`
        * `third_party/doctest/include/doctest`
        * `third_party/ut/include/boost`
    * Catch1 is no longer supported as a test framework, in order to better support more CMake build layouts. (#64)
        * Catch2 remains fully supported.
        * Catch1's main benefit was that it supported pre-C++11 compilers, but as ApprovalTests.cpp requires C++11 or newer, this wasn't useful in practice
* **New features**
    * Greatly improved and documented [CMake Integration](/doc/CMakeIntegration.md#top) (#69):
        * Approval Tests can now be added to other projects with any of  CMake's `add_subdirectory()`, `FetchContent` and `ExternalProject`. (#62, #65, #68, #75, #70, #88, #89)
        * Created wrapper [ApprovalTests.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/ApprovalTests.hpp)
 so that code can work interchangeably with the single header and via CMake integration (#89)
        * Made CMake targets for targets in third_party consistent with those of the original projects, adding `Catch2::Catch2`, `doctest::doctest` and `boost.ut` (#70)
        * Created a namespaced CMake target for ApprovalTests `ApprovalTests::ApprovalTests` (#75)
        * Don't create third_party targets if they have been created already (#88)
* **Bug fixes**
    * Significant effort to improve behaviour with the Ninja build tool:
        * Understood, work-around and documented issues with the Ninja generator.  See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top) if you have test failures in your Ninja builds. (#74 - thanks @jwillikers)
        * Added compile-time checks for GoogleTest, Catch2 and doctest, to detect problems with `__FILE__` macro caused by the Ninja generator on all platforms (#79 - thanks @jwillikers).
        * Added option to disable the `__FILE__` compile-time check (#86)
    * Project now works with [Unity builds](https://onqtam.com/programming/2018-07-07-unity-builds/) (#86)
* **Other changes**
    * Updated \[Boost\].UT integration to work with [a change](https://github.com/boost-experimental/ut/commit/94220e8c95b323349bfd94ef30b2568916fb1421#diff-04c6e90faac2675aa89e2176d2eec7d8) made for the v1.1.5 release of that library. (#66 - thanks @krzysztof-jusiak)
    * Code now formatted with clang-format (#39 - thanks @dheater and @alastairUK)
        * See [Formatting Code](/doc/Contributing.md#formatting-code) to configure your editor to use the [.clang-format](https://github.com/approvals/ApprovalTests.cpp/blob/master/.clang-format) file automatically.
    * Added CI build for clang-cl (#30 - thanks @alastairUK))
    * Added [CI builds for mingw/MSYS and CygWin](https://ci.appveyor.com/project/isidore/approvaltests-cpp/history) (#79)
    * Added CI builds for Ninja generator (#74)
    * The help text for problem misconfigured `main()` functions now links straight to the [relevant help page](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TroubleshootingMisconfiguredMain.md#top). (#84)
