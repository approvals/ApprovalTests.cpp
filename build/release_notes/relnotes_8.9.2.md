<!-- See the [v.8.9.2 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/__MILESTONE_NUMBER__?closed=1) for the full list of changes. -->

## DON'T PANIC!

We expect most of our users to have no problem with this upgrade. Source code is totally backwards-compatible, as long as you don't treat compiler warnings as errors. Even if you do, it only applies when:

 1. you are passing in a specific reporter, which is usually an infrequent and temporary coding state,
 2. you call `verifyWithExtension()`. 

## Deprecating verify(..., Reporter)

This is the second of a series of rapid releases, to make small steps in deprecating passing in a Reporter object, in favor of an Options object, to the `verify*()` methods. See [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top) for easy ways to update your code.

1. deprecation warnings are off: users can opt-in (v.8.7.0)
1. deprecation warnings are on: users can opt-out (v.8.9.1)
1. deprecation warnings are forced, code still exists (v.8.9.2)  <== you are here
1. the deprecated methods are hidden: users can opt-in
1. the deprecated methods are removed

* **Breaking changes**
    * None
* **New features**
    * None
* **Bug fixes**
    * None
* **Other changes**
    * `APPROVAL_TESTS_SHOW_DEPRECATION_WARNINGS` is now ignored. Warnings are always shown when using the `verify*()` methods that took a Reporter.
