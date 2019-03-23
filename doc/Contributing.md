<a id="top"></a>

# Contributing to ApprovalTests.cpp

**Contents**
<!-- vscode-markdown-toc -->
* [Documentation](#Documentation)
	* [Creating new pages](#Creatingnewpages)
	* [Adding code and file samples](#Addingcodeandfilesamples)
	* [Updating the tables of contents](#Updatingthetablesofcontents)
* [Releases](#Releases)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

## <a name='Documentation'></a>Documentation

We welcome improvements to the documentation! Here's how we manage the documentation files. 

### <a name='Creatingnewpages'></a>Creating new pages

If creating a new Markdown page, please make a copy of [doc/TemplatePage.md](../doc/TemplatePage.md).
This contains some boilerplate text which is tedious to create by hand. 

If the new page will be outside of the [doc](../doc/) folder, delete the following lines at the end:

```
---
   
[Back to User Guide](README.md#top)
```

### <a name='Addingcodeandfilesamples'></a>Adding code and file samples

We use Simon Cropp's [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) tool to embed source code and other files in Markdown pages.

**How it works:**

* Call the source file `[something].source.md`.
* See the [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) documentation for how to:
    * annotate snippets of source code, 
    * reference the snippets in documentation.
* Run  `mdsnippets` **before commit**, every time a `.source.md` file is updated
    * See [run_markdown_templates.sh](../run_markdown_templates.sh).
    * This will update the machine-generated `[something].md` files.

### <a name='Updatingthetablesofcontents'></a>Updating the tables of contents

We currently use [Joffrey Kern's "Markdown TOC"](https://marketplace.visualstudio.com/items?itemName=joffreykern.markdown-toc) Visual Studio Code extension to generate the **Contents** lists at the top of each Markdown page.

**How it works:**

* First install [the extension](https://marketplace.visualstudio.com/items?itemName=joffreykern.markdown-toc)
* Run  `Markdown TOC` **before commit**, every time headings of level 2 and above are updated
    * Open the markdown file in Visual Studio Code
    * Open the command palette (`Ctrl+Shift+P`)
    * Type "Generate"
    * Choose "Generate TOC for markdown"

## <a name='Releases'></a>Releases

* Everything for releases is in [the build directory](../build/)
* There's more information in [How To Release](../build/HowToRelease.md#top)

---

[Back to User Guide](README.md#top)
