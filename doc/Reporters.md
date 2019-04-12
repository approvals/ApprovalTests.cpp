<!--
This file was generate by MarkdownSnippets.
Source File: /doc/Reporters.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# Put Title Here

**Contents**

<!-- vscode-markdown-toc -->
* [Registering a default reporter](#Registeringadefaultreporter)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

## <a name='Registeringadefaultreporter'></a>Registering a default reporter

At present, the default Reporter is the DiffReporter. Whenever you call Approvals, you have the chance to pass in your own Reporter. However, if you would like to change what the default reporter is when you don't pass in a specific Reporter, you can do this at a global or per-test level, by adding the line:

<!-- snippet: use_as_default_reporter_in_main -->
```cpp
// main.cpp:
#include <memory>
auto defaultReporterDisposer = Approvals::useAsDefaultReporter( std::make_shared<DiffReporter>() );
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L14-L18)</sup>
<!-- endsnippet -->

The return value will restore the original reporter when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

---

[Back to User Guide](README.md#top)
