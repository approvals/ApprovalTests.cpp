See the [vNext milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/4?closed=1) for the full list of changes.

See also this list of [recently-fixed issues that don't yet have a milestone](https://github.com/approvals/ApprovalTests.cpp/issues?utf8=✓&q=is%3Aclosed+no%3Amilestone+updated%3A%3E%3D2019-12-20+sort%3Aupdated-desc).

* **Breaking changes**
    * None
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
