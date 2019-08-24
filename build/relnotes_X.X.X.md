* **Breaking changes**
    * We have removed `using std::string;` from all our code. If you happen to have code that worked accidentally because our usings brought in `string`, you might need to update your code.
* **New features**
    * Enable testing of [multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top).
    * Add ability to [register a custom namer](/doc/Namers.md#registering-a-custom-namer), to change the naming conventions for approved and received files.
    * Add custom namer to put saved and approved files in `approved/` and `received/` sub-directories. See [SeparateApprovedAndReceivedDirectoriesNamer](/doc/Namers.md#separateapprovedandreceiveddirectoriesnamer).
    * Add `[[nodiscard]]` for when compiling with C++17 or newer, so the compiler will point out any uses of disposer objects that are not stored.
* **Bug fixes**
    * Check file streams are valid before using them.
* **Other changes**
    * Adopted [Contributor Covenant v1.4](/CODE_OF_CONDUCT.md)
