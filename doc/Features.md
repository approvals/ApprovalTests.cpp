<!--
This file was generate by MarkdownSnippets.
Source File: /doc/Features.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# Features

**Contents**

<!-- vscode-markdown-toc -->
* [Using sub-directories for approved files](#Usingsub-directoriesforapprovedfiles)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

## <a name='Usingsub-directoriesforapprovedfiles'></a>Using sub-directories for approved files

If you have a lot of approval files, you might want to put them in a subdirectory, to prevent them cluttering up your source files. You can do this at a global or per-test level, by adding the line:

<!-- snippet: use_subdirectory_in_main -->
```cpp
auto directory = Approvals::useApprovalsSubdirectory("approval_tests");
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L9-L11)</sup>
<!-- endsnippet -->

The return value will restore the original directory when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

This mechanism allows you to select a different sub-directory in individual tests.


---

[Back to User Guide](README.md#top)
