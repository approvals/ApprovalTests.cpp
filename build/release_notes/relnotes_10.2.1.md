<!-- See the [v.10.2.1 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

**Note**: because `DateUtilities` is brand-new and barely used, we are releasing this as a patch release, to properly convey risk.

* **Breaking changes**
    * `time_t DateUtilities::toUTC(std::tm& timeinfo)` renamed to `DateUtilities::toUtc()`
* **New features**
    * Added `tm DateUtilities::toUtc(time_t& tt)`
* **Bug fixes**
    * Fix Visual Studio compiler warning C4996 due to use of `gmtime()` (#150)
        * This also fixes the Visual Studio builds of the Starter Project, which failed to compile due to the C4996 warning being treated as an error
* **Other changes**
    * None
