See the [v.8.7.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/8?closed=1) for the full list of changes.

* **Breaking changes**
    * **Planned deprecation:** The overloads of `verify()`, `verifyAll()` and `verifyAllCombinations()` which take a `Reporter` have been deprecated.
        * The `Reporter` argument is replaced by `Options` - see below.
        * By default, there is currently no change, but this release marks the start of the [plan to remove the deprecated methods](/doc/explanations/WhyWeAreConvertingToOptions.md#the-plan).
    * If you happen to have specialised `StringUtils::toString()`, you would now need to specialize `StringMaker::toString()` instead.
        * Note: this was previously unsupported behavior, so we are not bumping the major version number.
        * Here is how to update your code:
```diff
template <>
-std::string ApprovalTests::StringUtils::toString(const StringMakerPrintable& printable)
+std::string ApprovalTests::StringMaker::toString(const StringMakerPrintable& printable)
```
* **New features**
    * New [Scrubber](/doc/how_tos/ScrubNonDeterministicOutput.md#top) feature for working with non-deterministic output.  (#126, thank you @abdulg, @haraldreingruber, @jawn)
    * New [Options](/doc/Options.md#top) class provides consistent interface for customising the following in all `verify()`, `verifyAll()` and `verifyAllCombinations()` calls:
        * Reporter: see [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top)
        * Scrubber: see [How to Scrub Non-Deterministic Output](/doc/how_tos/ScrubNonDeterministicOutput.md#top)
        * File extensions now customizable with `verifyAll()` and `verifyAllCombinations()`: See [File Extensions](/doc/Options.md#file-extensions) (#127)
    * New mechanics for [String conversions](/doc/ToString.md#top) (thank you @alepez)
        * The class `Approvals` is now an alias for `TApprovals< ToStringCompileTimeOptions< StringMaker > >`
        * `CombinationApprovals` is now an alias for the class `TCombinationApprovals< ToStringCompileTimeOptions<APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER > >`, instead of being a namespace.
        * This is a completely backwards-compatible feature.
        * It has been done to support a new feature in a future release. (#124)
    * Our Conan.io package now supports our Boost.Test integration (#121)
* **Bug fixes**
    * None
* **Other changes**
    * [User Guide available on Read the Docs](https://approvaltestscpp.readthedocs.io/en/latest/index.html)
        * This is more easily searchable and better formatted than on GitHub, and a PDF download is available. (#129)
    * Documented workarounds for when [running Catch2 tests in CLion gives 'unexpected exception'](/doc/Troubleshooting.md#running-catch2-tests-in-clion-gives-unexpected-exception) (#131)
    * Consistent macro names
        * All our Macros now start with `APPROVAL_TESTS_`.
        * We have kept the old macros, redirecting to the new ones, for backwards compatibility.


| Old                                        | New                                       |
| ------------------------------------------ | ----------------------------------------- |
| `APPROVALTESTS_VERSION`                    | `APPROVAL_TESTS_VERSION`                  |
| `APPROVALTESTS_VERSION_MAJOR`              | `APPROVAL_TESTS_VERSION_MAJOR`            |
| `APPROVALTESTS_VERSION_MINOR`              | `APPROVAL_TESTS_VERSION_MINOR`            |
| `APPROVALTESTS_VERSION_PATCH`              | `APPROVAL_TESTS_VERSION_PATCH`            |
| `APPROVALTESTS_VERSION_STR`                | `APPROVAL_TESTS_VERSION_STR`              |
| `APPROVALS_CATCH_DISABLE_FILE_MACRO_CHECK` | `APPROVAL_TESTS_DISABLE_FILE_MACRO_CHECK` |
