Test cases
==========

anchor called top is removed
----------------------------

`“Target 1” <DisposableObjects.html>`__

other anchors are retained
--------------------------

`requirements for using Approval Tests With
[Boost].UT <UsingUT.html#requirements>`__.

anchor with unusal characters in is updated correctly
-----------------------------------------------------

`TCR <Glossary.html#test-commit-revert-tcr>`__.

`Existing Project - with your
main() <UsingCatch.html#existing-project-with-your-main>`__.

link to markdown file outside doc/ is unchanged
-----------------------------------------------

`How To
Release <https://github.com/approvals/ApprovalTests.cpp/blob/master/build/HowToRelease.md#top>`__

links to docs in various relative paths are correct
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

See `Target 1 <subdir1/Doc1.html#target1>`__.

See `Target 1 <subdir/Doc1.html#target1>`__.

See `Target 1 <Doc1.html#target1>`__.

Multiple links on one line
--------------------------

See `Target 1 <Doc1.html#target1>`__ join1 `Target
2 <Doc2.html#target3>`__ join2 `Target 3 <Doc3.html#target3>`__.

Links to directories
~~~~~~~~~~~~~~~~~~~~

`the build
directory <https://github.com/approvals/ApprovalTests.cpp/tree/master/build>`__

`doc <https://github.com/approvals/ApprovalTests.cpp/tree/master/doc>`__.

`/ApprovalTests/integrations/ <https://github.com/approvals/ApprovalTests.cpp/tree/master/ApprovalTests/integrations>`__

Links to source files
---------------------

`tests/GoogleTest_Tests/main.cpp <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/GoogleTest_Tests/main.cpp>`__

Links to .include.md files
--------------------------

`include_using_test_frameworks_list.include.md <https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/include_using_test_frameworks_list.include.md#top>`__

Links to images
---------------

Tutorial |Intro Graphic|

Tutorial |New Failure|

Link to README.md should go to GitHub
-------------------------------------

Link to README.md should go to GitHub, because README.md is not intended
to be displayed on Read the Docs.

Each new documentation page needs to be added to
`doc/README.md <https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/README.md#top>`__.

Non-HTML links - should be unchanged
------------------------------------

`Llewellyn <mailto:llewellyn.falco@gmail.com>`__

Do not change specific links that are in code blocks
----------------------------------------------------

.. code:: md

   * [this link will work everywhere](/doc/Reporters.md#top)

Not this:

.. code:: md

   * [this link is wrong](doc/Reporters.md#top)

And not this:

.. code:: md

   * [this link is wrong](Reporters.md#top)

Links whose hyperlinked text is in fixed-width font
===================================================

From Namers.md:

The interface for this is
`ApprovalNamer <https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalNamer.h>`__.

From CMakeIntegration.md:

`ExternalProject
module <https://cmake.org/cmake/help/latest/module/ExternalProject.html>`__

`add_subdirectory() <https://cmake.org/cmake/help/latest/command/add_subdirectory.html>`__.

From UsingUT.md

`std::source_location <https://en.cppreference.com/w/cpp/utility/source_location>`__

From Setup.md

`tests/NewTest.cpp <https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/NewTest.cpp>`__

Multiple on one line

`ExternalProject
module <https://cmake.org/cmake/help/latest/module/ExternalProject.html>`__
and ``this should still be fixed width`` and
`add_subdirectory() <https://cmake.org/cmake/help/latest/command/add_subdirectory.html>`__.

Test code snippet - linking to lines in a file
----------------------------------------------

.. code:: cpp

   ApprovalTests::Approvals::verifyExceptionMessage([]() { /* your code goes here */ });

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/ApprovalsExamples.cpp#L6-L8>`__)

Test code snippet - linking to a whole file
-------------------------------------------

::

   TITLE


   input.value1 => placeholder
   input.value2 => placeholder

(See `snippet
source <https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/approval_tests/VectorTests.VerifyAllStartingPoint.approved.txt#L1-L6>`__)

Test changes made to satisfy Pygments
-------------------------------------

Convert h to cpp
~~~~~~~~~~~~~~~~

.. code:: cpp

   class Wibble
   {
   };

Remove txt
~~~~~~~~~~

::

   I am some text

A wide table
------------

+-------------+-----------+--------------------+-----------------------+-------------+
| Framework   | Min C++   | Ease of setup      | IDE Support           | Build time  |
+=============+===========+====================+=======================+=============+
| Catch2      | C++11     | Very easy [1], [2] | Widely supported      | Not bad [3] |
+-------------+-----------+--------------------+-----------------------+-------------+
| doctest     | C++11     | Very easy [1]      | Unknown               | Fast        |
+-------------+-----------+--------------------+-----------------------+-------------+
| Google Test | C++11     | Difficult          | Very widely supported | Fast        |
+-------------+-----------+--------------------+-----------------------+-------------+
| Boost.Test  | C++11     | Difficult          | Unknown               | Fast        |
+-------------+-----------+--------------------+-----------------------+-------------+
| [Boost].UT  | C++20 [4] | Very easy [1]      | Unknown               | Fast        |
+-------------+-----------+--------------------+-----------------------+-------------+

1. Released as a single header file
2. See the `Starter
   Project <https://github.com/approvals/ApprovalTests.Cpp.StarterProject>`__
3. Catch2 has `options to speed up its
   builds <https://github.com/catchorg/Catch2/blob/master/docs/slow-compiles.md#top>`__
4. [Boost].UT works with C++17, but the ApprovalTests interface to that
   library depends on
   `std::source_location <https://en.cppreference.com/w/cpp/utility/source_location>`__,
   which is a C++ 20 feature.

A table with wide words
-----------------------

Some of these words end up with spaces in, wrongly.

+-----------------------------------+----------------------------------+
| Old                               | New                              |
+===================================+==================================+
| ``APPROVALTESTS_VERSION``         | ``APPROVAL_TESTS_VERSION``       |
+-----------------------------------+----------------------------------+
| ``APPROVALTESTS_VERSION_MAJOR``   | ``APPROVAL_TESTS_VERSION_MAJOR`` |
+-----------------------------------+----------------------------------+
| ``APPROVALTESTS_VERSION_MINOR``   | ``APPROVAL_TESTS_VERSION_MINOR`` |
+-----------------------------------+----------------------------------+
| ``APPROVALTESTS_VERSION_PATCH``   | ``APPROVAL_TESTS_VERSION_PATCH`` |
+-----------------------------------+----------------------------------+
| ``APPROVALTESTS_VERSION_STR``     | ``APPROVAL_TESTS_VERSION_STR``   |
+-----------------------------------+----------------------------------+
| ``APPROVALS                       | ``APPROVAL_                      |
| _CATCH_DISABLE_FILE_MACRO_CHECK`` | TESTS_DISABLE_FILE_MACRO_CHECK`` |
+-----------------------------------+----------------------------------+

Included file
-------------

-  `Using Approval Tests With Catch <UsingCatch.html>`__\ 
-  `Using Approval Tests With CppUTest <UsingCppUTest.html>`__
-  `Using Approval Tests With Google Tests <UsingGoogleTests.html>`__
-  `Using Approval Tests With Doctest <UsingDoctest.html>`__
-  `Using Approval Tests With Boost.Test <UsingBoostTest.html>`__
-  `Using Approval Tests With [Boost].UT <UsingUT.html>`__\ 

Snippet pulled in from external CMake file
------------------------------------------

Sample take from CMakeIntegration.md:

We use this ``dependencies/CMakeLists.txt`` file:

.. code:: cmake

   # Needs CMake 3.14 or above
   include(FetchContent)

   # -------------------------------------------------------------------
   # ApprovalTests.cpp
   FetchContent_Declare(ApprovalTests
           GIT_REPOSITORY https://github.com/approvals/ApprovalTests.cpp.git
           GIT_TAG master)

   FetchContent_MakeAvailable(ApprovalTests)

   # -------------------------------------------------------------------
   # Catch2
   FetchContent_Declare(Catch2
           GIT_REPOSITORY https://github.com/catchorg/Catch2.git
           GIT_TAG v2.11.1)

   FetchContent_MakeAvailable(Catch2)

(See `snippet
source <https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/main/./fetch_content_approvaltests_catch2/dependencies/CMakeLists.txt>`__)

Hyperlink and URL
-----------------

Does not render correctly on Read the Docs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Where a run of formatted text (here, italic) contains a hyperlink. I
have not been able to get it to display correctly in Read the Docs.

Example Markdown input, where the whole line is italic:

*If you would like us to add any more questions here, please contact us
via*\ `the Contributing page <Contributing.html>`__\ *.*

On the production site, it displays like this (after our conversion
process here):

::

   If you would like us to add any more questions here, please contact us via `the Contributing page <Contributing.html>`__.

*If you would like us to add any more questions here, please contact us
via*\ `the Contributing page <Contributing.html>`__\ *.*

Does render correctly on Read the Docs
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The fix is to end the italic formatting before the hyperlink. It looks a
bit worse on GitHub but a lot better in Read the Docs:

*If you would like us to add any more questions here, please contact us
via* `the Contributing page <Contributing.html>`__.

.. |Intro Graphic| image:: https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true
.. |New Failure| image:: https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/images/tutorial/01_new_failure.png?raw=true
