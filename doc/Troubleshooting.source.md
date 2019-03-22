<a id="top"></a>

<!-- vscode-markdown-toc -->
* [Test gives "You have forgotten to configure your test framework..."](#TestgivesYouhaveforgottentoconfigureyourtestframework...)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

# Troubleshooting

## <a name='TestgivesYouhaveforgottentoconfigureyourtestframework...'></a>Test gives "You have forgotten to configure your test framework..."

**Root Cause**:

A problem in your test program's `main()` means that ApprovalTests.cpp is not correctly set up for your test framework. 

**Symptom**

Running tests gives the following output:

```
************************************************************************************
*                                                                                  *
* Welcome to Approval Tests.
* 
* You have forgotten to configure your test framework for Approval Tests.
* 
* To do this in Catch, add the following to your main.cpp:
* 
*     #define APPROVALS_CATCH
*     #include "ApprovalTests.hpp"
* 
* To do this in Google Test, add the following to your main.cpp:
* 
*     #define APPROVALS_GOOGLETEST
*     #include "ApprovalTests.hpp"
* 
* For more information, please visit:
* https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/GettingStarted.md
*                                                                                  *
************************************************************************************
```

**Things to check:**

* Have you created a `main.cpp` that sets up ApprovalTests?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, copy in the non-comment code from [ApprovalTests_Catch2_Tests/main.cpp](/ApprovalTests_Catch2_Tests/main.cpp)
* Is your `main.cpp` included in your project's build?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, e.g. check your `CMakeLists.txt` file
* Does your Google Test have its own custom `main.cpp`?
    * If so, perhaps you haven't yet added the code to set up Approval Tests?
    * To fix, copy in the Approvals-specific lines from [examples/googletest_existing_main/main.cpp](/examples/googletest_existing_main/main.cpp)
* Is your code calling `Approvals::verify()` or any other methods in this library from outside a Google Test?
    * This is much less likely to be the cause, but the file-naming code in Approval Tests (`ApprovalTestNamer`) does require that approvals are used from inside a test method in a supported test framework. 

---

[Back to User Guide](README.md#top)
