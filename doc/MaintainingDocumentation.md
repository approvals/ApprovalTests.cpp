<a id="top"></a>

# Maintaining the Docs

<!-- toc -->
## Contents

  * [Purpose of this page](#purpose-of-this-page)
  * [Future version numbers](#future-version-numbers)
  * [Creating new pages](#creating-new-pages)
  * [Linking to new pages](#linking-to-new-pages)
    * [In Sphinx for Read the Docs](#in-sphinx-for-read-the-docs)
    * [In the GitHub User Guide](#in-the-github-user-guide)
  * [Internal links need to be absolute](#internal-links-need-to-be-absolute)
  * [Adding code and file samples](#adding-code-and-file-samples)
    * [How it works](#how-it-works)
    * [Managing CMake code samples](#managing-cmake-code-samples)
  * [Checking the documentation](#checking-the-documentation)
    * [Automated checking of links in documentation](#automated-checking-of-links-in-documentation)
    * [Other checks of documentation](#other-checks-of-documentation)<!-- endToc -->

## Purpose of this page

We welcome improvements to the documentation! Here's how we manage the _content_ of the documentation files. 

For information on how that content is built and published, see [Building the Docs](/doc/BuildingDocumentation.md#top).

## Future version numbers

To refer to the next release, use 'v.x.y.z', and make sure that there is a step to edit the file to update that text to the actual version number in the release scripts.

## Creating new pages

**Using the template page manually**

If creating a new Markdown page, please make a copy of [doc/TemplatePage.md](https://raw.githubusercontent.com/approvals/ApprovalTests.cpp/master/doc/TemplatePage.md#top).
This contains some boilerplate text which is tedious to create by hand.

**Creating one or more pages by script**

If creating multiple files, on Unix, you can use the script `doc/create_page.sh`

```bash
cd doc/
./create_page.sh TestingSingleObjects TestingContainers TestingCombinations
```

This won't overwrite existing files.
It will write out the text to paste in to other .md files, to correctly link to the new file. 

**For documentation files outside of doc**

If the new page will be outside of the [doc](/doc/) folder, delete the following lines at the end:

```md
---
   
[Back to User Guide](/doc/README.md#top)
```

## Linking to new pages

Two files need to be edited when new pages are added, so the new file is visible to users.

### In Sphinx for Read the Docs

Each new documentation page needs to be added twice in [doc/sphinx/index.rst](/doc/sphinx/index.rst).

1. A line beginning `:doc:`, which includes the page in the [Read the Docs front page](https://approvaltestscpp.readthedocs.io/en/latest/).
2. A link in a `.. toctree::` section, which includes the page in the navigation panel.

Note that Sphinx detects a page's title automatically, and will use it for the text in the hyperlink automatically, so you only need to spell out the link's text if you want it to be different from the page's title.

### In the GitHub User Guide

Each new documentation page needs to be added to [doc/README.md](/doc/README.md#top).

The layout here should mimic the layout generated you used in `index.rst`.

## Internal links need to be absolute 

All references to other files in this project, such as hyperlinks and images, must specify the full path from the root of the repository. This is needed for links to work correctly on the Read the Docs.

For example, use this:

```md
* [this link will work everywhere](/doc/Reporters.md#top)
```

Not this:

```md
* [this link is wrong](doc/Reporters.md#top)
```

And not this:

```md
* [this link is wrong](Reporters.md#top)
```

## Adding code and file samples

We use Simon Cropp's [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) tool to embed source code and other files in Markdown pages.

### How it works

* See the [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets) documentation for how to:
    * annotate snippets of source code, 
    * reference the snippets in documentation.
* Run  `run_markdown_templates.sh` **before commit**, every time a `.md` file or any of the source code with snippets is updated
    * See [run_markdown_templates.sh](/run_markdown_templates.sh).
    * This will update the tables of contents and and any snippets in all .md files in the project.
    * If this does not work, see that script for how to install the tools it uses

### Managing CMake code samples

The repository [claremacrae/ApprovalTests.cpp.CMakeSamples](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples) has some sample CMake projects for using ApprovalTests.cpp in various development scenarios.

When I improve the files in that repo, I run its script [claremacrae/ApprovalTests.cpp.CMakeSamples/create_markdown.py](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/blob/master/create_markdown.py) to convert the interesting CMake files to Markdown.

Some of those Markdown files are then embedded in the documentation for this project.

* See [CMakeIntegration.md](/doc/CMakeIntegration.md#top) for the final result.

## Checking the documentation

### Automated checking of links in documentation

There is a "markdown-link-check" github workflow that checks for broken links all in the Markdown files. It checks for missing file names, but will not detect missing anchors.

* It runs the script [scripts/check_links.sh](/scripts/check_links.sh) ...
* ... which uses the configuration file [mlc_config.json](/mlc_config.json) ...
* ... and runs [tcort's markdown-link-check](https://github.com/tcort/markdown-link-check)

If there are any failures, the output is slightly verbose to look through - you have to find lines beginning `[*]`, but I think that these will be sufficiently few and far between that this is good enough.

### Other checks of documentation

The script [fix_markdown.sh](/fix_markdown.sh) can be used to do some checks of the Markdown documentation files.

---

[Back to User Guide](/doc/README.md#top)
