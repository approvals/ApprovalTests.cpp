Using Approval Tests With Catch
===============================

Getting Started With Catch2
---------------------------

The `Catch2 <https://github.com/catchorg/Catch2>`__ test framework works
well with Approval Tests.

This section describes the various ways of using Approval Tests with
Catch2.

**Note:** Approval Tests has some specific build requirements if it is
built with the `Ninja build generator <https://ninja-build.org/>`__.
**If you use Ninja with Approval Tests, special care is needed when
setting up builds**, to avoid compilation errors or test failures. If
you have any problems with this, please see `Troubleshooting
Misconfigured Build </doc/TroubleshootingMisconfiguredBuild.md#top>`__.

Requirements
~~~~~~~~~~~~

Approval Tests requires that a file called the following is found:

.. raw:: html

   <!-- snippet: required_header_for_catch -->

.. code:: cpp

   #include <catch2/catch.hpp>

snippet source

(Before v7.0.0, it required ``Catch.hpp``)

Starter Project
~~~~~~~~~~~~~~~

The quickest way to start experimenting with Approval Tests is to:

1. Download the project
   `ApprovalTests.cpp.StarterProject <https://github.com/approvals/ApprovalTests.cpp.StarterProject>`__
   - via the green “Clone or Download” button at the top-right of the
   project site.
2. Opening the project in the C++ IDE of your choice.

Each time we release a new version of Approval Tests, we update this
project, so it always has the latest features.

New Project
~~~~~~~~~~~

Create a file ``main.cpp`` and add just the following two lines:

.. raw:: html

   <!-- snippet: catch_2_main -->

.. code:: cpp

   // main.cpp:
   #define APPROVALS_CATCH // This tells Approval Tests to provide a main() - only do this in one cpp file
   #include "ApprovalTests.hpp"

snippet source

Existing Project - with CATCH_CONFIG_MAIN
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have a Catch2 project with your own ``main.cpp`` that contains
the following lines, you will need to replace them with the code in the
previous section.

.. code:: cpp

   #define CATCH_CONFIG_MAIN // remove these lines, and replace with Approval Tests lines
   #include "catch2/catch.hpp"

.. raw:: html

   <!-- todo: document use of sections -->

Existing Project - with your main()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have `supplied your own ``main()`` for
Catch <https://github.com/catchorg/Catch2/blob/master/docs/own-main.md#top>`__,
you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that
contains ``main()``.

.. raw:: html

   <!-- snippet: catch_existing_main -->

.. code:: cpp

   // Add these two lines to the top of your main.cpp file:
   #define APPROVALS_CATCH_EXISTING_MAIN
   #include "ApprovalTests.hpp"

snippet source
