<a id="top"></a>

<!-- vscode-markdown-toc -->
* [Using sub-directories for approved files](#Usingsub-directoriesforapprovedfiles)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

# Features

## <a name='Usingsub-directoriesforapprovedfiles'></a>Using sub-directories for approved files

If you have a lot of approval files, you might want to put them in a subdirectory, to prevent them cluttering up your source files. You can do this at a global or per-test level, by adding the line:

snippet: use_subdirectory_in_main

The return value will restore the original directory when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

This mechanism allows you to select a different sub-directory in individual tests.


---

[Back to User Guide](README.md#top)
