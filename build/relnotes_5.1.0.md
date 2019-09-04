* **Breaking changes**
    * None
* **New features**
    * Approval tests will now [never launch any reporters on supported Continuous Integration machines](/doc/BuildMachinesAndCI.md#top)
    * [Approving multiple files in one test](/doc/MultipleOutputFilesPerTest.md#approving-multiple-files-in-one-test)
    * [ExceptionCollector](/doc/Utilities.md#exceptioncollector)
    * `Approvals::verify(custom_writer)`: see [Using custom writers](/doc/Writers.md#using-custom-writers)
    * `Approvals::verifyWithExtension(object, ".html")`: see [Using custom filename extensions](/doc/Writers.md#using-custom-filename-extensions)
* **Bug fixes**
    * The default namer is now used everywhere 
* **Other changes**
    * New documentation:
        * [All Customizations of Approval Tests](/doc/AllCustomizations.md#top)
        * [Utilities](/doc/Utilities.md#top)
        * [Writers](/doc/Writers.md#top)
        * [Build Machines and Continuous Integration servers](/doc/BuildMachinesAndCI.md#top)
        * [Definition of Done](/doc/Contributing.md#definition-of-done) - reminders to ourselves, mainly
    * Lots more code quality improvements, thanks to @alastairUK
