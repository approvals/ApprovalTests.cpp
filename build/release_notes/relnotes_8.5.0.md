See the [v.8.5.0 milestone](https://github.com/approvals/ApprovalTests.cpp/milestone/7?closed=1) for the full list of changes.

* **Breaking changes**
    * None
* **New features**
    * Added support for [Sublime Merge](https://www.sublimemerge.com/) on Linux, macOS, and Windows (#103, thank you @jwillikers)
    * Added support for [Beyond Compare](https://www.scootersoftware.com) on Linux (#114)
    * Added support for custom main() function with doctest: see [Existing Project - with your main()](/doc/UsingDoctest.md#existing-project---with-your-main) (#110, thank you @p-podsiadly)
    * Added support for Azure Pipelines, Azure DevOps Server and TFS CI systems (#117)
* **Bug fixes**
    * Code now compiles in clang and gcc with `-Wshadow` enabled (#111)
    * Fixed some missing '\\' characters in the released header (#118)
* **Other changes**
    * Updated to doctest 2.3.7 (#108, thank you @p-podsiadly)
    * New section in documentation: [How-to Guides](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/README.md#how-to-guides)
    * Lots of improvements to our Python release scripts
    * Line-length increased from 80 to 90 characters
