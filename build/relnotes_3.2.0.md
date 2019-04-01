* **Breaking changes**
    * None
* **New features**
    * Added `Approvals::useApprovalsSubdirectory()` which gives the ability to [write approved files to subdirectory](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#Usingsub-directoriesforapprovedfiles) 
        * **TODO** maybe move this documentation from Features to a more permanent location before publishing? 
    * Added `Approvals::verifyExceptionMessage()` which gives the ability to [check the text of excetion messages](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/TestingExceptions.md#top)
    * `StringWriter` now writes a useful message if the file cannot be opened (for example, because the path contains a non-existent directory)
* **Bug fixes**
    * None 
* **Other changes**
    * None
