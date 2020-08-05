<!-- See the [v.x.y.z milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * None
* **Bug fixes**
    * Fix Visual Studio compiler warning C4996 due to use of `gmtime()` (#150)
        * This also fixes the Visual Studio builds of the Starter Project, which failed to compile due to the C4996 warning being treated as an error
* **Other changes**
    * None
