<a id="top"></a>

# Building Documentation

toc

## Introduction

## 'doc' Directory Structure

### mdsnippets and Markdown Files

* Input files:
    * `mdsource/*.source.md`
    * `explanations/mdsource/*.source.md`
    * `how_tos/mdsource/*.source.md`
    * `mdsource/*.include.md`
      * Get included in generated *.md files
    * `https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples)/*.include.md`
      * Machine-generated files for included in Conan and CMake docs
* Output Files:
    * `*.md`
    * `explanations/*.md`
    * `how_tos/.*md`

![Flow of Markdown files through mdsnippets](/doc/images/mdsnippets_flow.png?raw=true)

### Images

* `images/*`
  * Images for inclusion in docs
* `images/tutorial/*`
  * Images for inclusion in docs
* `images/source/*`
  * Sources for some of the images.
* `images/source/generate_images.py`
  * Script that generates images from some source files.

### Doxygen Files

| Inputs                 | Outputs |
| ---------------------- | ------- |
| `mdsource/*.source.md` | `*.md`  |

![Doxygen Files](/doc/images/doxygen_flow.png?raw=true)


### ReStructured Text Files

| Inputs              | Outputs                                    |
| ------------------- | ------------------------------------------ |
| `sphinx/index.rst`  |                                            |
| `sphinx/api/*.rst`  |                                            |
| `*.md`              | `sphinx/generated_docs/*.rst`              |
| `explanations/*.md` | `sphinx/generated_docs/explanations/*.rst` |
| `how_tos/*.md`      | `sphinx/generated_docs/how_tos/*.rst`      |

![Sphinx Files](/doc/images/sphinx_flow.png?raw=true)

### Other Files to Explain

<!-- List created with tree -f -F -i doc | pbcopy -->


```text
doxygen/
doxygen/CMakeLists.txt
doxygen/Doxyfile.in

doxygen_docs/
doxygen_docs/group_macros_for_users.dox

requirements.txt

run_mdsnippets/
run_mdsnippets/CMakeLists.txt

sphinx/
sphinx/CMakeLists.txt
sphinx/__init__.py
sphinx/_templates/
sphinx/_templates/breadcrumbs.html
sphinx/api/
sphinx/conf.py
sphinx/markdown_conversion.py

sphinx/tests/
sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.md
sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.rst
sphinx/tests/__init__.py
sphinx/tests/test_markdown_conversion.py
sphinx/tests/test_markdown_conversion_input.md

```


## CMake Targets

## Doxygen

## RunMdsnippets

## Sphinx



---

[Back to User Guide](/doc/README.md#top)
