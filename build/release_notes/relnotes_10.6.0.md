<!-- See the [v.10.6.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * Approvals::verify() counts as an assertion in test frameworks. (#148)
        * This works in all currently-supported test frameworks.
        * Previously, Approvals wouldn't register as an assertion, giving misleading messages and reporting, and
          sometimes causing a test framework to complain that there were no assertions.
    * FrameworkIntegrations class
        * We now have a centralised portal, `FrameworkIntegrations`, to all the places that you need to use, in order
          to [add support for a new test framework](/doc/SupportingNewTestFramework.md#top).
* **Bug fixes**
    * None
* **Other changes**
    * None
