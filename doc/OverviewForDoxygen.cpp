/*! \mainpage ApprovalTests.cpp

 Purpose of document: state my understanding of the content, structure and implementation,
 for checking with Llewellyn.

 \section contents Contents

 - \ref overview
 - \ref supported_test_frameworks
 - \ref verification
 - \ref reporters
     - \ref reporters_overview
     - \ref custom_reporters
     - \ref reporters_implementation
 - \ref namers
 - \ref writers
 - \ref utilities
 - \ref tests

 \section overview Overview

 This library provides a variety of powerful, convenient, flexible functions for
 verifying that string or image representations of one or more objects match a
 previously-supplied representation.

 To allow any differences in those representations to be investigated and handle, it
 provides an abstraction with many flexible options. See \ref reporters below.

 And it uses one of a number of supported C++ test frameworks to supply the naming
 conventions of the files representing these objects, and to log any errors that occur.
 See \ref supported_test_frameworks.

 \note Where individual file names are referenced below, these are the locations in the source code.
 During the release process, all these files are combined together into a single header-only
 source file: see https://github.com/approvals/ApprovalTests.cpp/releases

 \section supported_test_frameworks Supported Test Frameworks

 The following test frameworks are currently supported, via these files:

 - Catch2Approvals.h
 - GoogleTestApprovals.h
 - OkraApprovals.h

 Might be worth creating a sub-directory for these, perhaps integrations, or test_frameworks?

 \section verification Verification Classes

 \todo Add overview of verification

 - Approvals is the main class that contains methods for verification
 - CombinationApprovals contains a powerful way of approving a large amount of data very easily
 - FileApprover is the core of this mechanism.
    - One overload of FileApprover::verify(ApprovalNamer&, ApprovalWriter&, const Reporter&) pulls together
      ApprovalNamer,  ApprovalWriter and Reporter, to run a verification
    - The other overload of FileApprover::verify(std::string, std::string) takes the
      names of two files, and decides if their contents
      are equivalent, ignoring differences in line endings
 - Use of exceptions
    - The way that a difference in file-content is conveyed by FileApprover to the test framework (Catch2, Google Test etc) is by
      the throwing of an exception. The test framework then picks up that exception, and reports it as a
      failure.
    - This means that, currently, it's only possible for a single verification failure to easily be reported
      by the test framework.
    - A test that wanted to run multiple verifications could catch ApprovalException, note the failure, keep on
      testing, and then at the end of the test method, call the test frameworks's specific mechanism to report
      the failure(s).
 - Exception types
    - It looks like FileApprover::verify() intends to throw ApprovalMissingException or ApprovalMismatchException
      to indicate failure
    - In fact, it throws ApprovalException

 \section reporters Reporters

 \todo Add overview of reporters

 \subsection reporters_overview Overview of Reporters

 - Reporter is the interface class
 - The default reporter is DiffReporter, which finds looks for one of a wide range of pre-configured
   file-comparison tools.
    - This is very convenient. It saves developers from having to find out what diffing tools are
      available on the current machine. One is chosen automatically

 \subsection custom_reporters Custom Reporters

 There are some reporters that are provided for convenience, to customise the way that any
 differences between approved and received results are displayed

 - ClipboardReporter is a reporter that puts a command on the system clipboard, that can
   be executed to move the received file to the approved one.
    - How does ClipboardReporter work if there are multiple verification failures during
      a test run. Does each invocation of ClipboardReporter over-write the clipboard
      contents from the previous invocation?
 - CombinationReporter allows all in a series reporters to be used for each verification
 - FirstWorkingReporter allows the first successful reporter from a series to be used for each verification
 - QuietReporter is a reporter that does nothing. Failing tests will still fail,
   but nothing will be launched.
 - If there is a differencing tool that you have installed, and that is not pre-defined
   by this library, you can look CommandLauncher and CommandReporter, to construct your own
   reporter object.

 \subsection reporters_implementation Implementation of Reporters

 - LinuxReporters.h, MacReporters.h, and WindowsReporters.h contain platform-specific classes
   for using the various pre-configured tools
 - DiffReporter.h then combines together all the platform-specific classes
 - DiffPrograms.h contains macros that are used to define the pre-configured tools
 - See also DiffInfo

 <hr>

 \section namers Implementation Detail: Namers

 The namer classes determine locations used for storing approved and received files.

 - ApprovalNamer is the interface class
 - Use ApprovalTestNamer the names of both these files are determined by the names of your test functions.
   This is the most common case.
    - ApprovalTestNamer::currentTest() provides access to the current test, which is a TestName
 - Use ExistingFileNamer if you have already created the received file yourself.
    -  This is really an implementation detail of Approvals::verifyExistingFile()

 \section writers Implementation Detail: Writers

 The writer classes provide an abstraction for converting an object to a file.

 - ApprovalWriter is the interface class
    - Could be moved to writers folder
 - StringWriter
    - Could be moved to writers folder
 - ExistingFile is a special-case writer
    - This is really an implementation detail of Approvals::verifyExistingFile()
    - It would be good to have a way to optionally tell ExistingFile::CleanUpReceived() to
      remove the received file.

 \section utilities Implementation Detail: Utilities

 - FileUtils
 - Macros.h
 - StringUtils
 - SystemUtils

 \section tests Tests of Approvals itself

 - ApprovalTests_Catch1_Tests
    - Tests integration with Catch1
 - ApprovalTests_Catch2_Tests
    - Tests both Approvals.cpp and its integration with Catch2
    - Would be good to add new sub-directories 'namers' and 'writers', to make structure consistent with that if
      the source code in ApprovalTests.
 - ApprovalTests_GoogleTest_Tests
    - Tests integration with Google Test

 */