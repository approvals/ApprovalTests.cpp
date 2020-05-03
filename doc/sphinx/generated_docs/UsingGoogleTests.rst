Using Approval Tests With Google Tests
======================================

Getting Started With Google Test
--------------------------------

The `Google Test <https://github.com/google/googletest>`__ test
framework works well with Approval Tests.

This section describes the various ways of using Approval Tests with
Google Test.

**Note:** Approval Tests has some specific build requirements if it is
built with the `Ninja build generator <https://ninja-build.org/>`__.
**If you use Ninja with Approval Tests, special care is needed when
setting up builds**, to avoid compilation errors or test failures. If
you have any problems with this, please see `Troubleshooting
Misconfigured Build </doc/TroubleshootingMisconfiguredBuild.md#top>`__.

Starter Project
~~~~~~~~~~~~~~~

We haven’t yet provided a Starter Project for using Approval Tests with
Google Tests.

This is partly based on the assumption that anyone already using Google
Tests will have their own project set up, and anyone else would probably
use Catch2 instead.

If it would be helpful for us to such a Starter Project, please let us
know, via the contact details in `Contributing to
ApprovalTests.cpp </doc/Contributing.md#top>`__.

New Project
~~~~~~~~~~~

Create a file ``main.cpp`` and add just the following two lines:

.. raw:: html

   <!-- snippet: googletest_main -->

.. code:: cpp

   // main.cpp:
   #define APPROVALS_GOOGLETEST // This tells Approval Tests to provide a main() - only do this in one cpp file
   #include "ApprovalTests.hpp"

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/main.cpp#L2-L6>`__)

Existing Project - no main()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Google Test has a ``gtest_main`` library that provides a ``main()``
function, and then runs all your tests.

If your existing Google Test application uses the ``gtest_main``
library, Approval Tests will not be able to obtain the names to use
output files. You will then see the help message shown in
`Troubleshooting </doc/Troubleshooting.md#top>`__.

To fix this, please add a new ``main.cpp``, as shown in the previous
section.

Existing Project - with your main()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have an existing Google Test-based test program that provides its
own ``main()``, you won’t be able to use the approach above.

Instead, you should make the following additions to your own source file
that contains ``main()``.

.. raw:: html

   <!-- snippet: googletest_existing_main -->

.. code:: cpp

   // main.cpp:

   // 1. Add these two lines to your main:
   #define APPROVALS_GOOGLETEST_EXISTING_MAIN
   #include "ApprovalTests.hpp"

   int main(int argc, char** argv)
   {
       ::testing::InitGoogleTest(&argc, argv);

       // 2. Add this line to your main:
       ApprovalTests::initializeApprovalTestsForGoogleTests();

       return RUN_ALL_TESTS();
   }

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/examples/googletest_existing_main/main.cpp#L1-L17>`__)

Customizing Google Tests Approval File Names
--------------------------------------------

Most testing frameworks have two pieces of naming information:
``SourceFileName`` and ``TestName``.

Google Tests has an additional piece of information: ``TestCaseName``.

.. raw:: html

   <!-- snippet: googletest_name_parts -->

.. code:: cpp

   TEST(TestCaseName, TestName)

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L13-L15>`__)

With Google Tests, this will result in Approvals creating output files
beginning with:

.. code:: text

   SourceFileName.TestCaseName.TestName

Very often, the ``SourceFileName`` and the ``TestCaseName`` are
redundant, meaning that what you would like is:

.. code:: text

   SourceFileName.TestName

By default, Approval Tests will do this if ``TestCaseName`` is
completely contained within ``SourceFileName``, meaning it is a
sub-string.

Customizing
~~~~~~~~~~~

If this is not enough, Approvals allows for customization, in two ways.

**Note:** to be able to add these pieces of code outside of a function,
you need to hold on to the result as a variable. This variable is not
used, it is only there to allow the method to execute.

**Note:** using these customizations inside a Google ``TEST`` or
``TEST_F``, is too late for that test: they won’t take effect until the
next executed test.

**Note:** this customization is permanent: it affects all tests run
later in the current program run.

**Note:** this customization is cannot be reversed.

Custom Suffixes
^^^^^^^^^^^^^^^

For example, if you are Google test fixtures, you might have a lot of
class names of the format ``TestClassNameFixture``. You can tell
Approval Tests that these are the same by adding the following to your
main:

.. raw:: html

   <!-- snippet: googletest_customize_suffix -->

.. code:: cpp

   // main.cpp
   auto customization = GoogleConfiguration::addIgnorableTestCaseNameSuffix("Fixture");

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L8-L11>`__)

Custom Anything
^^^^^^^^^^^^^^^

If you have something more unique, you can write a function that will
match if the test case name and the source file names should be
considered equal.

For example, let’s say you want a special tag ``IgnoreThis`` to indicate
a that a TestCaseName should be ignored, when determining the names of
output files.

So:

.. raw:: html

   <!-- snippet: googletest_customize_test -->

.. code:: cpp

   TEST(TestCaseName_IgnoreThis, TestName)

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L61-L63>`__)

Would produce an output file beginning with:

.. raw:: html

   <!-- snippet: googletest_customize_test_name -->

.. code:: cpp

   auto outputFileBaseName = "GoogleFixtureNamerCustomizationTests.TestName";

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L67-L69>`__)

You could achieve this by registering a function pointer like this:

.. raw:: html

   <!-- snippet: googletest_customize_function -->

.. code:: cpp

   // main.cpp
   bool dropTestCaseNamesWithIgnoreThis(const std::string& /*testFileNameWithExtension*/,
                                        const std::string& testCaseName)
   {
       return StringUtils::contains(testCaseName, "IgnoreThis");
   }

   auto ignoreNames =
       GoogleConfiguration::addTestCaseNameRedundancyCheck(dropTestCaseNamesWithIgnoreThis);

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L40-L50>`__)

Or by using a lambda like this:

.. raw:: html

   <!-- snippet: googletest_customize_lambda -->

.. code:: cpp

   // main.cpp
   auto ignoreNamesLambda = GoogleConfiguration::addTestCaseNameRedundancyCheck(
       [](const std::string& /*testFileNameWithExtension*/,
          const std::string& testCaseName) {
           return StringUtils::contains(testCaseName, "IgnoreThis");
       });

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/namers/GoogleFixtureNamerCustomizationTests.cpp#L52-L59>`__)
