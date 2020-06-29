<a id="top"></a>

# Building Documentation

toc

## Introduction

## 'doc' Directory Structure



### Key

| Format   | Description                        |
| -------- | ---------------------------------- |
| **Bold** | Source file, maintained by a human |
| Non-bold | Machine-generated file             |



### Markdown Files



| Inputs                                    | Outputs               |
| ----------------------------------------- | --------------------- |
| **doc/mdsource/\*.source.md**              | doc/\*.md              |
| **doc/mdsource/\*.include.md** |  |
| **doc/explanations/mdsource/\*.source.md** | doc/explanations/\*.md |
| **doc/how_tos/mdsource/\*.source.md**      | doc/how_tos/.*md      |



### Images



| Files                      | Comments                                                     |
| -------------------------- | ------------------------------------------------------------ |
| **doc/images/\***          | Images for inclusion in docs                                 |
| **doc/images/tutorial/\*** | Images for inclusion in docs                                 |
| **doc/images/source/\***   | Sources for some of the images. Note that there is no system to update the generated images if the source images change. |



### Doxygen Files

| Inputs                                    | Outputs               |
| ----------------------------------------- | --------------------- |
| **doc/mdsource/\*.source.md**              | doc/\*.md              |



### ReStructured Text Files

| Inputs                   | Outputs                                      |
| ------------------------ | -------------------------------------------- |
| **doc/sphinx/index.rst** |                                              |
| **doc/sphinx/api/\*.rst** |                                              |
| doc/\*.md                 | doc/sphinx/generated_docs/\*.rst              |
| doc/explanations/\*.md    | doc/sphinx/generated_docs/explanations/\*.rst |
| doc/how_tos/\*.md          | doc/sphinx/generated_docs/how_tos/\*.rst       |



<!-- List created with tree -f -F -i doc | pbcopy -->


```text
doc
doc/doxygen/
doc/doxygen/CMakeLists.txt
doc/doxygen/Doxyfile.in
doc/doxygen/OverviewForDoxygen.cpp
doc/doxygen_docs/
doc/doxygen_docs/group_macros_for_users.dox

doc/mdsource/create_page.sh*
doc/mdsource/file_link.sh*
doc/mdsource/page_link.sh*
doc/requirements.txt
doc/run_mdsnippets/
doc/run_mdsnippets/CMakeLists.txt
doc/sphinx/
doc/sphinx/CMakeLists.txt
doc/sphinx/__init__.py

doc/sphinx/_templates/
doc/sphinx/_templates/breadcrumbs.html
doc/sphinx/api/

doc/sphinx/conf.py

doc/sphinx/markdown_conversion.py
doc/sphinx/tests/
doc/sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.md
doc/sphinx/tests/TestWholeConversion.test_convert_github_markdown_for_input_to_pandoc_in_root_docdir.approved.rst
doc/sphinx/tests/__init__.py
doc/sphinx/tests/test_markdown_conversion.py
doc/sphinx/tests/test_markdown_conversion_input.md

```


## CMake Targets

## Doxygen

## RunMdsnippets

## Sphinx



---

[Back to User Guide](/doc/README.md#top)
