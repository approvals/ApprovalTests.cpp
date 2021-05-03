Core Classes
============

.. note:: All classes and symbols listed here are in the ``ApprovalTests`` namespace.

ApprovalComparator
------------------

``ApprovalComparator`` is an interface that determines if received and approved files are equivalent.

For more information, see :doc:`../generated_docs/CustomComparators`.

.. doxygenclass:: ApprovalTests::ApprovalComparator
   :members:
   :undoc-members:

ApprovalException and subclasses
--------------------------------

``ApprovalException`` is the base class for ApprovalTest-specific exceptions.

.. doxygenclass:: ApprovalTests::ApprovalException
   :members:
   :undoc-members:

ApprovalMismatchException
^^^^^^^^^^^^^^^^^^^^^^^^^

``ApprovalMismatchException`` is thrown if received and approved files differ.

.. doxygenclass:: ApprovalTests::ApprovalMismatchException
   :members:
   :undoc-members:

ApprovalMissingException
^^^^^^^^^^^^^^^^^^^^^^^^

``ApprovalMissingException`` is thrown if the approved file is missing - typically on first run of a new test.

.. doxygenclass:: ApprovalTests::ApprovalMissingException
   :members:
   :undoc-members:

ApprovalNamer
-------------

``ApprovalNamer`` is the interface that controls how approved and received files are named.

For more information, see :doc:`../generated_docs/Namers`.

.. doxygenclass:: ApprovalTests::ApprovalNamer
   :members:
   :undoc-members:

ApprovalWriter
--------------

``ApprovalWriter`` is the interface that controls how objects being verified are written to disk.

For more information, see :doc:`../generated_docs/Writers`.

.. doxygenclass:: ApprovalTests::ApprovalWriter
   :members:
   :undoc-members:

FileApprover
------------

Low-level methods for approving files.

.. doxygenclass:: ApprovalTests::FileApprover
   :members:
   :undoc-members:

Options
--------

Easy control of various customization points in Approvals::verify() and similar methods

For more information, see :doc:`../generated_docs/Options`.

.. doxygenclass:: ApprovalTests::Options
   :members:
   :undoc-members:

Reporter and subclasses
-----------------------

Reporters are called on test failure, typically to show differences.

Most reporters launch an external diffing tool, allowing programmers
to understand the difference(s) between approved and received files. They
also typically allow the output to be "approved".

For a demonstration of this, see the :doc:`../generated_docs/Tutorial`.

For more information, see :doc:`../generated_docs/Reporters`.

.. doxygenclass:: ApprovalTests::Reporter
   :members:
   :undoc-members:

Linux Reporters
^^^^^^^^^^^^^^^

.. doxygennamespace:: ApprovalTests::Linux

macOS Reporters
^^^^^^^^^^^^^^^

.. doxygennamespace:: ApprovalTests::Mac

Windows Reporters
^^^^^^^^^^^^^^^^^

.. doxygennamespace:: ApprovalTests::Windows
