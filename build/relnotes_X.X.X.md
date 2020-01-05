See the [vNext milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/4?closed=1) for the full list of changes.

See also this list of [recently-fixed issues that don't yet have a milestone](https://github.com/approvals/ApprovalTests.cpp/issues?utf8=✓&q=is%3Aclosed+no%3Amilestone+updated%3A%3E%3D2019-12-20+sort%3Aupdated-desc).

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
* **New features**
    * None
* **Bug fixes**
    * None
* **Other changes**
    * Catch1 is no longer supported as a test framework, in order to better support more CMake build layouts. (#64)
        * Catch2 remains fully supported.
        * Catch1's main benefit was that it supported pre-C++11 compilers, but as ApprovalTests.cpp requires C++11 or newer, this wasn't useful in practice
    * Code now formatted with clang-format (#39 - thanks @dheater and @alastairUK)
    * Added CI build for clang-cl (#30 - thanks @alastairUK))
