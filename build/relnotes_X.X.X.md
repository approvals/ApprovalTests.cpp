* **Breaking changes**
    * Virtually all code is now in a new `ApprovalTests` namespace, and user code will need to be updated (#5). There are two approaches to updating your code:
        * Option 1: Explicitly add `ApprovalTests::` to your code, for example:
            ```diff
            -Approvals::verify("My objects!");
            +ApprovalTests::Approvals::verify("My objects!");
            ```

            ```diff
            -auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
            +auto directory = ApprovalTests::Approvals::useApprovalsSubdirectory("approval_tests");
            ```
        * Option 2: Add a `using` directive near the top of your test files:
            ```diff
            +using namespace ApprovalTests;
            ```
    * We have removed `using std::string;` from all our code. If you happen to have code that worked accidentally because our usings brought in `string`, you might need to update your code.
    * We have removed support for the [Okra](https://github.com/JayBazuzi/Okra) test framework, as we believe noone is using the integration, and it was a non-trivial amount of work to get it working again with changes we have made recently.
* **New features**
    * Enable testing of [multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top).
    * Add ability to [register a custom namer](/doc/Namers.md#registering-a-custom-namer), to change the naming conventions for approved and received files.
    * Add custom namer to put saved and approved files in `approved/` and `received/` sub-directories. See [SeparateApprovedAndReceivedDirectoriesNamer](/doc/Namers.md#separateapprovedandreceiveddirectoriesnamer).
    * Add `[[nodiscard]]` for when compiling with C++17 or newer, so the compiler will point out any uses of disposer objects that are not stored.
* **Bug fixes**
    * Check file streams are valid before using them.
* **Other changes**
    * Adopted [Contributor Covenant v1.4](/CODE_OF_CONDUCT.md)
