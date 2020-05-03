Using Approval Tests With [Boost].UT
====================================

Getting Started With [Boost].UT
-------------------------------

The `[Boost].UT <https://github.com/boost-experimental/ut>`__ test
framework works well with Approval Tests.

[Boost].UT is a single header/single module, macro-free μ(micro)/Unit
Testing Framework that requires C++17 / C++20

**Note:** Approval Tests has some specific build requirements if it is
built with the `Ninja build generator <https://ninja-build.org/>`__.
**If you use Ninja with Approval Tests, special care is needed when
setting up builds**, to avoid compilation errors or test failures. If
you have any problems with this, please see `Troubleshooting
Misconfigured Build </doc/TroubleshootingMisconfiguredBuild.md#top>`__.

Requirements
~~~~~~~~~~~~

Approval Tests for [Boost].UT requires that a file called the following
is found:

.. raw:: html

   <!-- snippet: required_header_for_ut -->

.. code:: cpp

   #include <boost/ut.hpp>

It also requires:

-  A C++ compiler that supports the C++ 20
   ```std::source_location`` <https://en.cppreference.com/w/cpp/utility/source_location>`__.
   See `C++ compiler
   support <https://en.cppreference.com/w/cpp/compiler_support>`__.
-  A build that enables C++20 - for example, with:
   ``set(CMAKE_CXX_STANDARD 20)``
-  A [Boost].UT version that is compatible with the version of
   ApprovalTests.cpp being used. See the version we test against:
   `third_party/ut/include/boost/ut.hpp <https://github.com/approvals/ApprovalTests.cpp/blob/master/third_party/ut/include/boost/ut.hpp>`__

Usage examples
~~~~~~~~~~~~~~

Add the following two lines to your source code:

.. raw:: html

   <!-- snippet: ut_main -->

.. code:: cpp

   #define APPROVALS_UT
   #include "ApprovalTests.hpp"

Below is an example of a call to an approval test inside a [Boost].UT
test:

.. raw:: html

   <!-- snippet: ut_main_usage -->

.. code:: cpp

   "ItCanVerifyAFile"_test = []() {
       Approvals::verify("Approval Tests can verify text via the golden master method");
   };

In the following example, two instances of ApprovalTests are called
inside the same test. We need to use sections with different names, to
prevent Approval Tests from using the same output file for both tests:

.. raw:: html

   <!-- snippet: ut_main_multiple -->

.. code:: cpp

   "ItCanUseMultipleVerify"_test = []() {
       {
           // Here we simulate test sections, so that Approval Tests uses different
           // output file names for the different verify() calls.
           auto section = NamerFactory::appendToOutputFilename("section 1");
           Approvals::verify(
               "Approval Tests can verify text via the golden master method");
       }
       {
           auto section = NamerFactory::appendToOutputFilename("section 2");
           Approvals::verify("Approval Tests can verify different text via "
                             "the golden master method");
       }
   };
