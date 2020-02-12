<!-- See the [v.8.3.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * `CustomReporter::create()` adds flexibility for adding custom merge tools: see [How To Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top) (#43)
    * Add support for Araxis Merge on Mac
    * Added support for GitHub Actions CI system - see [Build Machines and Continuous Integration servers](/doc/BuildMachinesAndCI.md#top)
* **Bug fixes**
    * Reporters now respect the arguments they are supplied with (#82)
* **Other changes**
    * Document [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top).
    * Lots of refactoring around reporters
    * Added
        * `ApprovalTests::FileUtils::readFileThrowIfMissing()` and
        * `ApprovalTests::FileUtils::readFileReturnEmptyIfMissing()`
