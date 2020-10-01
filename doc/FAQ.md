<a id="top"></a>

# Frequently Asked Questions

<!-- toc -->
## Contents

  * [Overview](#overview)
    * [What are approval tests?](#what-are-approval-tests)
    * [How do they differ from unit tests?](#how-do-they-differ-from-unit-tests)
    * [Why are approval tests particularly good for testing legacy code?](#why-are-approval-tests-particularly-good-for-testing-legacy-code)
  * [Test Frameworks](#test-frameworks)
    * [Do I need to use the Catch2 in the Approval Tests repo?](#do-i-need-to-use-the-catch2-in-the-approval-tests-repo)
    * [Does it integrate with other unit testing libraries?](#does-it-integrate-with-other-unit-testing-libraries)
  * [Writing Tests](#writing-tests)
    * [I wrote a test, but the output file has loads of stuff I'm not interested in](#i-wrote-a-test-but-the-output-file-has-loads-of-stuff-im-not-interested-in)
    * [I want to test images](#i-want-to-test-images)<!-- endToc -->

*If you would like us to add any more questions here, please contact us via* [the Contributing page](/doc/Contributing.md#top).

## Overview

### What are approval tests?

### How do they differ from unit tests?

### Why are approval tests particularly good for testing legacy code?

## Test Frameworks

### Do I need to use the Catch2 in the Approval Tests repo?

No. The intention is that you can provide your own copy of Catch2, via a file call `catch.hpp`.

We use the copy of Catch2 and other test frameworks in [third_party/](https://github.com/approvals/ApprovalTests.cpp/blob/master/third_party/) in this project only to run our own tests.

Certainly, if you download a [Single Header release](https://github.com/approvals/ApprovalTests.cpp/releases) of this library, no Catch2 is provided, so you need to provide your own.

### Does it integrate with other unit testing libraries?

## Writing Tests

### I wrote a test, but the output file has loads of stuff I'm not interested in

Things to say:

* Yes, it's a common problem
* Readability of the output is important
* Someone reviewing a test failure needs to understand the purpose and intent of the test
* **Recommendation**: write your own formatting that's specific to particular tests - see
    * [How to do String Conversions](/doc/ToString.md#top)
    * [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top) for examples.

### I want to test images

You may find that your tests fail, even though equivalent Approved and Received files are being compared, if the image file formats being used encode things like the date the file was created. This is because ApprovalTests.cpp's default behaviour is a character-for-character comparison of file content.

If you can use the Qt framework, then we have provided a way to verify the contents of PNG images: please see `ApprovalTestsQt::verifyQImage()` in [ApprovalTests.cpp.Qt](https://github.com/approvals/ApprovalTests.cpp.Qt).

---

[Back to User Guide](/doc/README.md#top)
