See also the [v.7.0.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/2?closed=1) for things that have been fixed since last release, and need to be recorded here.

* **Breaking changes**
    * If you pass in a reporter to CombinationApprovals::verifyAllCombinations(), the argument order has changed, and is now the first argument: see [Passing in a Reporter](/doc/TestingCombinations.md#passing-in-a-reporter). (#47 - thanks to @mika-fischer, Mika Fischer)
* **New features**
    * Support for differencing tools in Tortoise Git. Thanks to @lp55, Luiz Paulo M. Pires (#57)
* **Bug fixes**
    * Fixed unnecessary duplicate static functions. (#54)
    * Fixed ClipboardReporter on macOS. (#51)
* **Other changes**
    * Documentation improvements (Thanks to Neil Horlock)
