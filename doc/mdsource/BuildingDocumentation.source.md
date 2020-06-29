<a id="top"></a>

# Building Documentation

toc

## Introduction

## 'doc' Directory Structure


<!-- List created with tree -f -F -i doc | pbcopy -->


```text
doc
doc/AllCustomizations.md
doc/ApprovalTestingConcept.md
doc/ApprovingResults.md
doc/BuildMachinesAndCI.md
doc/BuildingDocumentation.md
doc/CMakeIntegration.md
doc/CMakeLists.txt
doc/CodingPatterns.md
doc/ConanIntegration.md
doc/Configuration.md
doc/Contributing.md
doc/CustomComparators.md
doc/DisposableObjects.md
doc/FAQ.md
doc/Features.md
doc/GettingStarted.md
doc/Glossary.md
doc/MaintainingDocumentation.md
doc/MultipleOutputFilesPerTest.md
doc/Namers.md
doc/Options.md
doc/Overview.md
doc/PathToApprovalTesting.md
doc/README.md
doc/Reporters.md
doc/Setup.md
doc/SupportingNewTestFramework.md
doc/TemplatePage.md
doc/TestingCombinations.md
doc/TestingContainers.md
doc/TestingExceptions.md
doc/TestingSingleObjects.md
doc/ToString.md
doc/Troubleshooting.md
doc/TroubleshootingMisconfiguredBuild.md
doc/TroubleshootingMisconfiguredMain.md
doc/Tutorial.md
doc/UsingBoostTest.md
doc/UsingCatch.md
doc/UsingDoctest.md
doc/UsingGoogleTests.md
doc/UsingUT.md
doc/Utilities.md
doc/Videos.md
doc/Writers.md
doc/doxygen/
doc/doxygen/CMakeLists.txt
doc/doxygen/Doxyfile.in
doc/doxygen/OverviewForDoxygen.cpp
doc/doxygen_docs/
doc/doxygen_docs/group_macros_for_users.dox
doc/explanations/
doc/explanations/Scrubbers.md
doc/explanations/TipsForDesigningStrings.md
doc/explanations/WhyWeAreConvertingToOptions.md
doc/explanations/mdsource/
doc/explanations/mdsource/Scrubbers.source.md
doc/explanations/mdsource/TipsForDesigningStrings.source.md
doc/explanations/mdsource/WhyWeAreConvertingToOptions.source.md
doc/how_tos/
doc/how_tos/ScrubNonDeterministicOutput.md
doc/how_tos/SubmitANewReporterToApprovalTests.md
doc/how_tos/TestAVarietyOfValues.md
doc/how_tos/TestContainerContents.md
doc/how_tos/ToggleDeprecatedCode.md
doc/how_tos/UseACustomReporter.md
doc/how_tos/UseTheFmtLibraryToPrintObjects.md
doc/how_tos/mdsource/
doc/how_tos/mdsource/ScrubNonDeterministicOutput.source.md
doc/how_tos/mdsource/SubmitANewReporterToApprovalTests.source.md
doc/how_tos/mdsource/TestAVarietyOfValues.source.md
doc/how_tos/mdsource/TestContainerContents.source.md
doc/how_tos/mdsource/ToggleDeprecatedCode.source.md
doc/how_tos/mdsource/UseACustomReporter.source.md
doc/how_tos/mdsource/UseTheFmtLibraryToPrintObjects.source.md
doc/how_tos/mdsource/updating_deprecated_code.include.md
doc/images/
doc/images/ApprovalTests.cpp.IntroGraphic.gif
doc/images/ApprovalTests_v.10.1.1_compilation_times.png
doc/images/ScrubberOverview.png
doc/images/source/
doc/images/source/ApprovalTests_v.10.1.1_compilation_times.pptx
doc/images/source/ScrubberOverview.drawio
doc/images/tutorial/
doc/images/tutorial/01_new_failure.png
doc/images/tutorial/02_approving.png
doc/images/tutorial/03_approved.png
doc/mdsource/
doc/mdsource/AllCustomizations.source.md
doc/mdsource/ApprovalTestingConcept.source.md
doc/mdsource/ApprovingResults.source.md
doc/mdsource/BuildMachinesAndCI.source.md
doc/mdsource/BuildingDocumentation.source.md
doc/mdsource/CMakeIntegration.source.md
doc/mdsource/CodingPatterns.source.md
doc/mdsource/ConanIntegration.source.md
doc/mdsource/Configuration.source.md
doc/mdsource/Contributing.source.md
doc/mdsource/CustomComparators.source.md
doc/mdsource/DisposableObjects.source.md
doc/mdsource/FAQ.source.md
doc/mdsource/Features.source.md
doc/mdsource/GettingStarted.source.md
doc/mdsource/Glossary.source.md
doc/mdsource/MaintainingDocumentation.source.md
doc/mdsource/MultipleOutputFilesPerTest.source.md
doc/mdsource/Namers.source.md
doc/mdsource/Options.source.md
doc/mdsource/Overview.source.md
doc/mdsource/PathToApprovalTesting.source.md
doc/mdsource/README.source.md
doc/mdsource/Reporters.source.md
doc/mdsource/Setup.source.md
doc/mdsource/SupportingNewTestFramework.source.md
doc/mdsource/TemplatePage.source.md
doc/mdsource/TestingCombinations.source.md
doc/mdsource/TestingContainers.source.md
doc/mdsource/TestingExceptions.source.md
doc/mdsource/TestingSingleObjects.source.md
doc/mdsource/ToString.source.md
doc/mdsource/Troubleshooting.source.md
doc/mdsource/TroubleshootingMisconfiguredBuild.source.md
doc/mdsource/TroubleshootingMisconfiguredMain.source.md
doc/mdsource/Tutorial.source.md
doc/mdsource/UsingBoostTest.source.md
doc/mdsource/UsingCatch.source.md
doc/mdsource/UsingDoctest.source.md
doc/mdsource/UsingGoogleTests.source.md
doc/mdsource/UsingUT.source.md
doc/mdsource/Utilities.source.md
doc/mdsource/Videos.source.md
doc/mdsource/Writers.source.md
doc/mdsource/create_page.sh*
doc/mdsource/file_link.sh*
doc/mdsource/include_ninja_warning_note.include.md
doc/mdsource/include_using_test_frameworks_list.include.md
doc/mdsource/page_link.sh*
doc/requirements.txt
doc/run_mdsnippets/
doc/run_mdsnippets/CMakeLists.txt
doc/sphinx/
doc/sphinx/CMakeLists.txt
doc/sphinx/Makefile
doc/sphinx/__init__.py
doc/sphinx/__pycache__/
doc/sphinx/__pycache__/markdown_conversion.cpython-37.pyc
doc/sphinx/_static/
doc/sphinx/_templates/
doc/sphinx/_templates/breadcrumbs.html
doc/sphinx/api/
doc/sphinx/api/approving.rst
doc/sphinx/api/core.rst
doc/sphinx/api/scrubbers.rst
doc/sphinx/conf.py
doc/sphinx/generated_docs/
doc/sphinx/generated_docs/AllCustomizations.rst
doc/sphinx/generated_docs/ApprovalTestingConcept.rst
doc/sphinx/generated_docs/ApprovingResults.rst
doc/sphinx/generated_docs/BuildMachinesAndCI.rst
doc/sphinx/generated_docs/BuildingDocumentation.rst
doc/sphinx/generated_docs/CMakeIntegration.rst
doc/sphinx/generated_docs/CodingPatterns.rst
doc/sphinx/generated_docs/ConanIntegration.rst
doc/sphinx/generated_docs/Configuration.rst
doc/sphinx/generated_docs/Contributing.rst
doc/sphinx/generated_docs/CustomComparators.rst
doc/sphinx/generated_docs/DisposableObjects.rst
doc/sphinx/generated_docs/FAQ.rst
doc/sphinx/generated_docs/Features.rst
doc/sphinx/generated_docs/GettingStarted.rst
doc/sphinx/generated_docs/Glossary.rst
doc/sphinx/generated_docs/MaintainingDocumentation.rst
doc/sphinx/generated_docs/MultipleOutputFilesPerTest.rst
doc/sphinx/generated_docs/Namers.rst
doc/sphinx/generated_docs/Options.rst
doc/sphinx/generated_docs/Overview.rst
doc/sphinx/generated_docs/PathToApprovalTesting.rst
doc/sphinx/generated_docs/README.rst
doc/sphinx/generated_docs/README.txt
doc/sphinx/generated_docs/Reporters.rst
doc/sphinx/generated_docs/Setup.rst
doc/sphinx/generated_docs/SupportingNewTestFramework.rst
doc/sphinx/generated_docs/TemplatePage.rst
doc/sphinx/generated_docs/TestingCombinations.rst
doc/sphinx/generated_docs/TestingContainers.rst
doc/sphinx/generated_docs/TestingExceptions.rst
doc/sphinx/generated_docs/TestingSingleObjects.rst
doc/sphinx/generated_docs/ToString.rst
doc/sphinx/generated_docs/Troubleshooting.rst
doc/sphinx/generated_docs/TroubleshootingMisconfiguredBuild.rst
doc/sphinx/generated_docs/TroubleshootingMisconfiguredMain.rst
doc/sphinx/generated_docs/Tutorial.rst
doc/sphinx/generated_docs/UsingBoostTest.rst
doc/sphinx/generated_docs/UsingCatch.rst
doc/sphinx/generated_docs/UsingDoctest.rst
doc/sphinx/generated_docs/UsingGoogleTests.rst
doc/sphinx/generated_docs/UsingUT.rst
doc/sphinx/generated_docs/Utilities.rst
doc/sphinx/generated_docs/Videos.rst
doc/sphinx/generated_docs/Writers.rst
doc/sphinx/generated_docs/explanations/
doc/sphinx/generated_docs/explanations/Scrubbers.rst
doc/sphinx/generated_docs/explanations/TipsForDesigningStrings.rst
doc/sphinx/generated_docs/explanations/WhyWeAreConvertingToOptions.rst
doc/sphinx/generated_docs/how_tos/
doc/sphinx/generated_docs/how_tos/ScrubNonDeterministicOutput.rst
doc/sphinx/generated_docs/how_tos/SubmitANewReporterToApprovalTests.rst
doc/sphinx/generated_docs/how_tos/TestAVarietyOfValues.rst
doc/sphinx/generated_docs/how_tos/TestContainerContents.rst
doc/sphinx/generated_docs/how_tos/ToggleDeprecatedCode.rst
doc/sphinx/generated_docs/how_tos/UseACustomReporter.rst
doc/sphinx/generated_docs/how_tos/UseTheFmtLibraryToPrintObjects.rst
doc/sphinx/index.rst
doc/sphinx/make.bat
doc/sphinx/markdown_conversion.py
doc/sphinx/tests/
doc/sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.md
doc/sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.rst
doc/sphinx/tests/__init__.py
doc/sphinx/tests/test_markdown_conversion.py
doc/sphinx/tests/test_markdown_conversion_input.md

20 directories, 201 files

```


## CMake Targets

## Doxygen

## RunMdsnippets

## Sphinx



---

[Back to User Guide](/doc/README.md#top)
