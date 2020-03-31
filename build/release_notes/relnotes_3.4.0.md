* **Breaking changes**
    * None
* **New features**
    * Added [AutoApproveIfMissingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Reporters.md#auto-approving)
    * Added [AutoApproveReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Reporters.md#auto-approving)
    * Added a mechanism to [shorten the names of output files, by omitting redundant Test Case Names, when using Google Test](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/UsingGoogleTests.md#customizing-google-tests-approval-file-names). 
    * Started adding hooks for TCR in Catch: [(test && commit || revert)](https://medium.com/@kentbeck_7670/test-commit-revert-870bbd756864)
* **Bug fixes**
    * Added virtual destructors for base classes with virtual methods
    * Suppress most unused-parameter warnings
    * Included `<stdexcept>` for `std::runtime_error` to fix build on Clang 5
* **Other changes**
    * In `ApprovalTestNamer`:
        * Added `getSourceFileName()`
        * Added `getOutputFileBaseName()`
        * Deprecated `getFileName()`
