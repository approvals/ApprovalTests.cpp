<!-- See the [v.x.y.z milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

* **Breaking changes**
    * None
* **New features**
    * [Conan](https://conan.io) Integration provided, and documented in [Conan Integration](/doc/ConanIntegration.md#top) ([Conan issue 741](https://github.com/conan-io/conan-center-index/pull/741), thank you @dheater)
* **Bug fixes**
    * 3 locations now throw an exception if their `system()` call failed. Previously they silently ignored the error. (#94, thank you @p-podsiadly)
        * `ClipboardReporter`
        * `SystemLauncher::launch()`
        * `FileUtilsSystemSpecific::copyFile()`
* **Other changes**
    * None
