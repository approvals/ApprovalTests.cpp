## DON'T PANIC!

We expect most of our users to have no problem with this upgrade. Changes are only needed when:

 1. you are passing in a specific reporter, which is usually an infrequent and temporary coding state,
 2. you call `verifyWithExtension(object, ".json")` is now  
    `Approvals::verify(object, Options().fileOptions().withFileExtension(".json"))`


## Removing verify(..., Reporter)

This is the fourth and final of a series of rapid releases, to make small steps in deprecating passing in a Reporter object, in favor of an Options object, to the `verify*()` methods. See [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top) for easy ways to update your code.

1. deprecation warnings are off: users can opt-in (v.8.7.0)
1. deprecation warnings are on: users can opt-out (v.8.9.1)
1. deprecation warnings are forced, code still exists (v.8.9.2)
1. the deprecated methods are hidden: users can opt-in (v.9.0.0)
1. the deprecated methods are removed (v.10.0.0)  <== you are here

* **Breaking changes**

    * Removed methods:
        * `Approvals::verify(..., Reporter)`
        * `Approvals::verifyAll(..., Reporter)`
        * `Approvals::verifyExistingFile(..., Reporter)`
        * `Approvals::verifyExceptionMessage(..., Reporter)`
        * `Approvals::verifyWithExtension(...)`
        * `CombinationApprovals::verifyAllCombinations(Reporter, ...)`
    * Removed macros:
        * `APPROVAL_TESTS_HIDE_DEPRECATED_CODE`
        * `APPROVALTESTS_VERSION`
        * `APPROVALTESTS_VERSION_MAJOR`
        * `APPROVALTESTS_VERSION_MINOR`
        * `APPROVALTESTS_VERSION_PATCH`
        * `APPROVALTESTS_VERSION_STR`
        * `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK`
    * The following macros have been changed.

| Old (removed)                              | New                                       |
| ------------------------------------------ | ----------------------------------------- |
| `APPROVALTESTS_VERSION`                    | `APPROVAL_TESTS_VERSION`                  |
| `APPROVALTESTS_VERSION_MAJOR`              | `APPROVAL_TESTS_VERSION_MAJOR`            |
| `APPROVALTESTS_VERSION_MINOR`              | `APPROVAL_TESTS_VERSION_MINOR`            |
| `APPROVALTESTS_VERSION_PATCH`              | `APPROVAL_TESTS_VERSION_PATCH`            |
| `APPROVALTESTS_VERSION_STR`                | `APPROVAL_TESTS_VERSION_STR`              |
| `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK` | `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` |

* **New features**
    * None
* **Bug fixes**
    * None
* **Other changes**
    * None

