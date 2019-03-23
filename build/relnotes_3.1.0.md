* **Breaking changes**
    * None
* **New features**
    * Added converter-based Approvals::verify(object, lambda_converter) overload - see #6
    * A helpful message is issued if main() is not set up correctly.
    * The library is now usable with CMake add_subdirectory() of source tree.
    * WinMerge can handle images
* **Bug fixes**
    * It's now possible to test non-copyable objects with Approvals::verify
    * Fixed compilation of tests on clang - see #6
    * Fixed compilation if later includes use EMPTY, STATIC or ENTRY - see #7
    * Fixed finding of programs on non-English Windows systems
* **Other changes**
    * Started work on a User Guide: https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/README.md
    * Created a Troubleshooting page: https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Troubleshooting.md
