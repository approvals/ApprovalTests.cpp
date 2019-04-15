* **Breaking changes**
    * Some methods on `DefaultReporter` have moved to `DefaultReporterFactory`
* **New features**
    * Added `BlockingReporter` which give the ability to [prevent launching on CI machines](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#blocking-reporter) 
    * Added `MachineBlocker` which gives the ability to [have tests that only run on your machine](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#machine-blockers).
    * Added `Approvals::useAsFrontLoadedReporter()` which gives the ability to [use BlockingReporter](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#front-loaded-reporters)
* **Bug fixes**
    * None  
* **Other changes**
    * None
