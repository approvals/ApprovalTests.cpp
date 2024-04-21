<a id="top"></a>

# ApprovalTests for C++

**ApprovalTests.cpp** is a C++ implementation of Approval Tests.

Also known as Golden Master Tests or Snapshot Testing, Approval Tests
are an alternative to asserts. They are great for testing objects with
lots of fields, or lists of objects.

**Note:** This User Guide is [**also available on Read the Docs**](https://approvaltestscpp.readthedocs.io/en/latest/), with easier navigation, search and a [PDF download](https://approvaltestscpp.readthedocs.io/_/downloads/en/latest/pdf/).

----

<!-- NOTE: This list needs to be updated by hand if new sections are added -->

*Contents:&nbsp;[Getting&nbsp;Started](#getting-started)
| [Test&nbsp;Frameworks](#test-frameworks)
| [Writing&nbsp;Tests](#writing-tests)
| [Customising&nbsp;Behaviour](#customising-behaviour)
| [Common&nbsp;Challenges](#common-challenges)
| [How-to&nbsp;Guides](#how-to-guides)
| [Build&nbsp;Systems](#build-systems)
| [Extras](#extras)
| [Troubleshooting](#troubleshooting)
| [Developing&nbsp;ApprovalTests.cpp](#developing-approvaltestscpp)
| [C++ Reference](#c-reference)*

----

## Getting Started

If you are new to Approval Tests, or to this C++ library, start here:

  - **Concepts**:
    [Overview](/doc/Overview.md#top) |
    [ApprovalTesting (the concept)](/doc/ApprovalTestingConcept.md#top) |
    [The Path to Approval Testing](/doc/PathToApprovalTesting.md#top) |
    [Approval Testing Concepts](https://github.com/approvals/ApprovalTests.Documentation/blob/main/explanations/approval_testing.md#top) |
    [Place to modify output](https://github.com/approvals/ApprovalTests.Documentation/blob/main/explanations/creating_output.md#top) | [What are Approvals](https://github.com/approvals/ApprovalTests.Documentation/blob/main/explanations/what_are_approvals.md#top) | [Benifits of Different Reporters](https://github.com/approvals/ApprovalTests.Documentation/blob/main/explanations/benefits_of_different_reporters.md#top)

  - **Start coding**:
    [Tutorial](/doc/Tutorial.md#top) |
    [Setup Options](/doc/Setup.md#top) |
    [Choosing a test framework](/doc/GettingStarted.md#top) |
    [Approving Results](/doc/ApprovingResults.md#top)

## Test Frameworks

Approval Tests uses a test framework, in order to find out the names of
tests and of source files. The test framework will also report errors
for any failed Approval Tests.

  - **Using Approval Tests with**:
    [Boost.Test](/doc/UsingBoostTest.md#top) |
    [Catch2](/doc/UsingCatch.md#top) |
    [CppUTest](/doc/UsingCppUTest.md#top) |
    [doctest](/doc/UsingDoctest.md#top) |
    [Google Tests](/doc/UsingGoogleTests.md#top) |
    [\[Boost\].ut](/doc/UsingUT.md#top)
  - **Extending test framework support**:
    [Supporting a new test framework](/doc/SupportingNewTestFramework.md#top)

## Writing Tests

Now that you are set up to run Approval Tests, this section describes
how to test various types of complex objects, and how to do so
effectively.

  - **How to Test**: [Single
    Objects](/doc/TestingSingleObjects.md#top) |
    [Containers](/doc/TestingContainers.md#top) |
    [Combinations of containers](/doc/TestingCombinations.md#top) |
    [Testing Exceptions](/doc/TestingExceptions.md#top)
  - **Good Practice**:
    [String conversions](/doc/ToString.md#top) |
    [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top)

## Customising Behaviour

  - **Principles**:
    [Options](/doc/Options.md#top) |
    [Disposable Objects](/doc/DisposableObjects.md#top)
  - **Customisation points**:
    [Reporters](/doc/Reporters.md#top) |
    [Comparators](/doc/CustomComparators.md#top) |
    [Writers](/doc/Writers.md#top) |
    [Namers](/doc/Namers.md#top) |
    [Scrubbers](/doc/explanations/Scrubbers.md#top) |
    [Configuring Approval Tests](/doc/Configuration.md#top)
  - **Summary**:
    [All Customizations of Approval Tests](/doc/AllCustomizations.md#top)

## Common Challenges

  - **Challenges**:
    [Multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top)

## How-to Guides

- **Writing Tests**:
    - [How to Test the Contents of a Container](/doc/how_tos/TestContainerContents.md#top)        
    - [How to Test a Variety of Values for One Input](/doc/how_tos/TestAVarietyOfValues.md#top)
    - [How to Scrub Non-Deterministic Output](/doc/how_tos/ScrubNonDeterministicOutput.md#top)
    - [How to Use the Fmt Library To Print Objects](/doc/how_tos/UseTheFmtLibraryToPrintObjects.md#top)
 - **Reporters**:
   - [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)
   - [How to Select a Reporter with an Environment Variable](/doc/how_tos/SelectReporterWithEnvironmentVariable.md#top)
   - [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top)
 - **Others**:
   - [How to Toggle Enabling or Disabling of Deprecated Code](/doc/how_tos/ToggleDeprecatedCode.md#top)

## Build Systems

  - **Integrations**:
    [CMake](/doc/CMakeIntegration.md#top) |
    [Conan](/doc/ConanIntegration.md#top) |
    [Vcpkg](/doc/VcpkgIntegration.md#top)
  - **Installation**:
    [Installation Via CMake](/doc/how_tos/InstallApprovalTestsUsingCMake.md#top)
  - **Your builds**:
    [Build Machines and CI servers](/doc/BuildMachinesAndCI.md#top)

## Extras

  - **Various**:
    [Features](/doc/Features.md#top) |
    [Why We Are Converting To Options](/doc/explanations/WhyWeAreConvertingToOptions.md#top) |
    [FAQs](/doc/FAQ.md#top) |
    [Glossary](/doc/Glossary.md#top) |
    [Utilities](/doc/Utilities.md#top) |
    [Videos](/doc/Videos.md#top)

## Troubleshooting

  - **Topics**:
    [Troubleshooting](/doc/Troubleshooting.md#top) |
    [Misconfigured Builds](/doc/TroubleshootingMisconfiguredBuild.md#top) |
    [Misconfigured main()](/doc/TroubleshootingMisconfiguredMain.md#top)

## Developing ApprovalTests.cpp

  - **Topics**:
    [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top) |
    [Coding Patterns](/doc/CodingPatterns.md#top) |
    [Maintaining the Docs](/doc/MaintainingDocumentation.md#top) |
    [Building the Docs](/doc/BuildingDocumentation.md#top)

## C++ Reference

This section contains a growing list of "Read the Docs" pages documenting the ApprovalTests.cpp API. It may be useful to see what methods, and overloads, are available. It is very short on descriptive text, as we focus our efforts on the documentation above.

<!-- NOTE: This list needs to be updated by hand if new pages are added -->

  - **Fundamentals**: [Approving Objects](https://approvaltestscpp.readthedocs.io/en/latest/api/approving.html) | [Core Classes](https://approvaltestscpp.readthedocs.io/en/latest/api/core.html) | [Scrubber Functions](https://approvaltestscpp.readthedocs.io/en/latest/api/scrubbers.html)

