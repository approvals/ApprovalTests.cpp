<a id="top"></a>

# How to Create a Custom Namer

<!-- toc -->
## Contents

  * [Overview](#overview)
  * [Supported tags](#supported-tags)
  * [](#)<!-- endToc -->

## Overview

The easiest way to create a custom namer is to use a `TemplatedCustomNamer`.

Here is an example:

<!-- snippet: templated_custom_namer_example -->
<a id='snippet-templated_custom_namer_example'></a>
```cpp
TemplatedCustomNamer namer("/my/source/directory/{ApprovedOrReceived}/"
                           "{TestFileName}.{TestCaseName}.{FileExtension}");
```
<sup><a href='/tests/DocTest_Tests/namers/CustomNamerTests.cpp#L9-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-templated_custom_namer_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Supported tags

<!-- snippet: custom_namer_tags -->
<a id='snippet-custom_namer_tags'></a>
```cpp
auto testSourceDirectory = "{TestSourceDirectory}";
auto testFileName = "{TestFileName}";
auto testCaseName = "{TestCaseName}";
auto approvedOrReceived = "{ApprovedOrReceived}";
auto fileExtension = "{FileExtension}";
```
<sup><a href='/ApprovalTests/namers/TemplatedCustomNamer.cpp#L33-L39' title='Snippet source file'>snippet source</a> | <a href='#snippet-custom_namer_tags' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

##  

```cpp
auto myNamer = CustomizableNamer()
    .withTestFolder([]{return "C:/ApprovalFiles";})
    .withTestFolderForReceived([]{return getTestFolder() + "/received"});

Approvals::verify("Hello World", Options().withNamer(myNamer));
```


---

[Back to User Guide](/doc/README.md#top)
