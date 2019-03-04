<!--
This file was generate by MarkdownSnippets.
Source File: \doc\Troubleshooting.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->

# Troubleshooting

## Google Test crashes in Approval Test function 

**Root Cause**:

A problem in your test program's `main()` means that ApprovalTests.cpp is not correctly set up for the Google Test framework. 

**Example symptoms:**

On Windows, a test gives `SEH exception with code 0xc0000005 thrown in the test body`, e.g.

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from GoogleTestApprovalsTests
[ RUN      ] GoogleTestApprovalsTests.TestStreamableObject
unknown file: error: SEH exception with code 0xc0000005 thrown in the test body.
[  FAILED  ] GoogleTestApprovalsTests.TestStreamableObject (4 ms)
[----------] 1 test from GoogleTestApprovalsTests (4 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (7 ms total)
[  PASSED  ] 0 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] GoogleTestApprovalsTests.TestStreamableObject

 1 FAILED TEST
 ```

On Linux, a test doesn't finish, and you get something like this:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from GoogleTestApprovalsTests
[ RUN      ] GoogleTestApprovalsTests.TestStreamableObject

Process finished with exit code 0
```

Instead of the usual:

```
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from GoogleTestApprovalsTests
[ RUN      ] GoogleTestApprovalsTests.TestStreamableObject
[       OK ] GoogleTestApprovalsTests.TestStreamableObject (13 ms)
[----------] 1 test from GoogleTestApprovalsTests (13 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (21 ms total)
[  PASSED  ] 1 test.

Process finished with exit code 0
```

**Things to check:**

* Have you created a `main.cpp` that sets up ApprovalTests?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, copy in the non-comment code from [ApprovalTests_Catch2_Tests/main.cpp](/ApprovalTests_Catch2_Tests/main.cpp)
* Is your `main.cpp` included in your project's build
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, e.g. check your `CMakeLists.txt` file
* Does your Google Test have its own custom `main.cpp`?
    * If so, perhaps you haven't yet added the code to set up Approval Tests?
    * To fix, copy in the Approvals-specific lines from [examples/googletest_existing_main/main.cpp](/examples/googletest_existing_main/main.cpp)
* Is your code calling `Approvals::verify()` or similar from outside a Google Test?
    * This is much less likely to be the cause, but the file-naming code in Approval Tests (`ApprovalTestNamer`) does require that approvals are used from inside a test method in a supported test framework. 

---

[Back to User Guide](README.md)
