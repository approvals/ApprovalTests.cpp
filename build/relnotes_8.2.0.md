See the [v.8.2.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/6?closed=1) for the full list of changes.

* **Breaking changes**
    * None
* **New features**
    * [Conan](https://conan.io/) Integration provided, and documented in [Conan Integration](/doc/ConanIntegration.md#top) ([Conan issue 741](https://github.com/conan-io/conan-center-index/pull/741), thank you @dheater)
* **Bug fixes**
    * 3 locations now throw an exception if their `system()` call failed. Previously they silently ignored the error. (#94, thank you @p-podsiadly)
        * `ClipboardReporter`
        * `SystemLauncher::launch()`
        * `FileUtilsSystemSpecific::copyFile()`
    * Fixed a bug that could break [custom comparators](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/CustomComparators.md#top), stopping them from taking effect, depending on how their disposers were stored (#93, thank you @p-podsiadly)
* **Other changes**
    * Windows.h no longer included in SystemUtils.h (#96, thank you @p-podsiadly)
