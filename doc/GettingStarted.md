<!--
This file was generate by MarkdownSnippets.
Source File: /doc/GettingStarted.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

<!-- vscode-markdown-toc -->
* [Catch 1 and 2](#Catch1and2)
	* [New Project](#NewProject)
	* [Existing Project](#ExistingProject)
* [Google Test](#GoogleTest)
	* [Starter Project](#StarterProject)
	* [New Project](#NewProject-1)
	* [Existing Project](#ExistingProject-1)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

# Getting Started

## <a name='Catch1and2'></a>Catch 1 and 2

### <a name='NewProject'></a>New Project

<!-- snippet: catch_2_main -->
```cpp
#define APPROVALS_CATCH
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L4-L7)</sup>
<!-- endsnippet -->

### <a name='ExistingProject'></a>Existing Project

TODO

## <a name='GoogleTest'></a>Google Test

### <a name='StarterProject'></a>Starter Project

TODO

### <a name='NewProject-1'></a>New Project

<!-- snippet: googletest_main -->
```cpp
#define APPROVALS_GOOGLETEST
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_GoogleTest_Tests/main.cpp#L2-L5)</sup>
<!-- endsnippet -->

### <a name='ExistingProject-1'></a>Existing Project

<!-- snippet: googletest_existing_main -->
```cpp
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
```
<sup>[snippet source](/examples/googletest_existing_main/main.cpp#L1-L11)</sup>
<!-- endsnippet -->

---

[Back to User Guide](README.md#top)
