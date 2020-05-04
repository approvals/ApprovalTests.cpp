ApprovalTests for C++
=====================

**ApprovalTests.cpp** is a C++ implementation of Approval Tests.

Also known as Golden Master Tests or Snapshot Testing, Approval Tests are an alternative to asserts. They are great for testing objects with lots of fields, or lists of objects.

.. note:: This documentation on Read the Docs is a work in progress. There will be broken links, missing images, and not-yet-stable URLS.

Getting Started
---------------

If you are new to Approval Tests, or to this C++ library, start here:

* **Concepts**:
  :doc:`Overview <generated_docs/Overview>` |
  :doc:`generated_docs/ApprovalTestingConcept` |
  :doc:`generated_docs/PathToApprovalTesting`

* **Start coding**:
  :doc:`generated_docs/Tutorial` |
  :doc:`generated_docs/Setup` |
  :doc:`Choosing a test framework <generated_docs/GettingStarted>` |
  :doc:`generated_docs/ApprovingResults`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: Getting Started

   generated_docs/Overview
   generated_docs/ApprovalTestingConcept
   generated_docs/PathToApprovalTesting

   generated_docs/Tutorial
   generated_docs/Setup
   generated_docs/GettingStarted
   generated_docs/ApprovingResults

Test Frameworks
---------------

Approval Tests uses a test framework, in order to find out the names of tests and of source files. The test framework will also report errors for any failed Approval Tests.

* **Using Approval Tests with**:
  :doc:`Boost.Test <generated_docs/UsingBoostTest>` |
  :doc:`Catch2 <generated_docs/UsingCatch>` |
  :doc:`doctest <generated_docs/UsingDoctest>` |
  :doc:`Google Tests <generated_docs/UsingGoogleTests>` |
  :doc:`[Boost].ut <generated_docs/UsingUT>`

* **Extending test framework support**:
  :doc:`generated_docs/SupportingNewTestFramework`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: Test Frameworks

   generated_docs/UsingBoostTest
   generated_docs/UsingCatch
   generated_docs/UsingDoctest
   generated_docs/UsingGoogleTests
   generated_docs/UsingUT
   generated_docs/SupportingNewTestFramework

Writing Tests
-------------

Now that you are set up to run Approval Tests, this section describes how to test various types of complex objects, and how to do so effectively.

* **How to Test**:
  :doc:`Single Objects<generated_docs/TestingSingleObjects>` |
  :doc:`Containers <generated_docs/TestingContainers>` |
  :doc:`Combinations of containers<generated_docs/TestingCombinations>` |
  :doc:`Exception messages <generated_docs/TestingExceptions>`

* **Good Practice**:
  :doc:`generated_docs/ToString`

.. toctree::
   :maxdepth: 1
   :hidden:
   :caption: Writing Tests

   generated_docs/TestingSingleObjects
   generated_docs/TestingContainers
   generated_docs/TestingCombinations
   generated_docs/TestingExceptions

   generated_docs/ToString

Customising Behaviour
---------------------

.. toctree::
   :maxdepth: 1
   :caption: Customising Behaviour

   generated_docs/DisposableObjects
   generated_docs/Reporters
   generated_docs/CustomComparators
   generated_docs/Writers
   generated_docs/Namers
   generated_docs/Configuration
   generated_docs/AllCustomizations

Common Challenges
-----------------

.. toctree::
   :maxdepth: 1
   :caption: Common Challenges

   generated_docs/MultipleOutputFilesPerTest

How-to Guides
-------------

.. toctree::
   :maxdepth: 1
   :caption: How-to Guides

   generated_docs/how_tos/TestContainerContents
   generated_docs/how_tos/TestAVarietyOfValues
   generated_docs/how_tos/UseACustomReporter
   generated_docs/how_tos/SubmitANewReporterToApprovalTests

Build Systems
-------------

.. toctree::
   :maxdepth: 1
   :caption: Build Systems

   generated_docs/CMakeIntegration
   generated_docs/ConanIntegration
   generated_docs/BuildMachinesAndCI

Extras
------

.. toctree::
   :maxdepth: 1
   :caption: Extras

   generated_docs/Features
   generated_docs/FAQ
   generated_docs/Glossary
   generated_docs/Utilities
   generated_docs/Videos

Troubleshooting
---------------

.. toctree::
   :maxdepth: 1
   :caption: Troubleshooting

   generated_docs/Troubleshooting
   generated_docs/TroubleshootingMisconfiguredBuild
   generated_docs/TroubleshootingMisconfiguredMain

Developing ApprovalTests.cpp
----------------------------

.. toctree::
   :maxdepth: 1
   :caption: Developing ApprovalTests.cpp

   generated_docs/Contributing
   generated_docs/CodingPatterns

C++ Reference
-------------

.. toctree::
   :maxdepth: 1
   :caption: C++ Reference

   approving
   core

Code Index
----------

* :ref:`genindex`
