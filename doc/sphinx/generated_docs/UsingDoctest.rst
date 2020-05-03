Using Approval Tests With doctest
=================================

Getting Started With doctest
----------------------------

The `doctest <https://github.com/onqtam/doctest>`__ test framework works
well with Approval Tests.

**Note:** Approval Tests has some specific build requirements if it is
built with the `Ninja build generator <https://ninja-build.org/>`__.
**If you use Ninja with Approval Tests, special care is needed when
setting up builds**, to avoid compilation errors or test failures. If
you have any problems with this, please see `Troubleshooting
Misconfigured Build </doc/TroubleshootingMisconfiguredBuild.md#top>`__.

Doctest is similar to Catch, but claims to give faster compilation
times.

Requirements
~~~~~~~~~~~~

Approval Tests for doctest requires that a file called the following is
found:

.. raw:: html

   <!-- snippet: required_header_for_doctest -->

.. code:: cpp

   #include <doctest/doctest.h>

Approval Tests needs doctest version 2.3.4 or above.

New Project
~~~~~~~~~~~

Create a file ``main.cpp`` and add just the following two lines:

.. raw:: html

   <!-- snippet: doctest_main -->

.. code:: cpp

   // main.cpp:
   #define APPROVALS_DOCTEST // This tells Approval Tests to provide a main() - only do this in one cpp file
   #include "ApprovalTests.hpp"

.. raw:: html

   <!-- todo: document use of sections -->

Existing Project - with your main()
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you have `supplied your own ``main()`` for
doctest <https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md#top>`__,
you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that
contains ``main()``.

.. raw:: html

   <!-- snippet: doctest_existing_main -->

.. code:: cpp

   // Add these two lines to the top of your main.cpp file:
   #define APPROVALS_DOCTEST_EXISTING_MAIN
   #include "ApprovalTests.hpp"
