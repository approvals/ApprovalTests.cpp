* **Breaking changes**
    * We have removed `using std::string;` from all our code. If you happen to have code that worked accidentally because our usings brought in `string`, you might need to update your code.
* **New features**
    * Add ability to [register a custom namer](/doc/Namers.md#registering-a-custom-namer), to change the naming conventions for approved and received files.
    * Add custom namer to put saved and approved files in `approved/` and `received/` sub-directories. See [SeparateApprovedAndReceivedDirectoriesNamer](/doc/Namers.md#separateapprovedandreceiveddirectoriesnamer).
* **Bug fixes**
    * Check file streams are valid before using them.
* **Other changes**
    * None
