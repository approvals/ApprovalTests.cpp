* **Breaking changes**
    * None
* **New features**
    * Added `Approvals::useApprovalsSubdirectory()` which gives the ability to [write approved files to subdirectory](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#Usingsub-directoriesforapprovedfiles) 
    * Added `Approvals::useAsDefaultReporter()` which gives the ability to [set the default reporter used in your system](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Reporters.md#registering-a-default-reporter).
    * Added `Approvals::verifyExceptionMessage()` which gives the ability to [check the text of exception messages](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TestingExceptions.md#top)
    * `StringWriter` now writes a useful message if the file cannot be opened (for example, because the path contains a non-existent directory)
* **Bug fixes**
    * Reporters will now launch correctly on cygwin, allowing failing tests to be fixed on this platform.  
* **Other changes**
    * None
