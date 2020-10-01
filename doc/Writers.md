<a id="top"></a>

# Writers

<!-- toc -->
## Contents

  * [Default Behaviour](#default-behaviour)
  * [Using custom writers](#using-custom-writers)
  * [Using custom filename extensions](#using-custom-filename-extensions)<!-- endToc -->

## Default Behaviour

By default, when Approval Tests verifies an object, it uses the [StringWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/writers/StringWriter.h) class to write out the string representation of the object.

And by default, `StringWriter` gives the saved file the extension `.txt`. 

`StringWriter` implements the [ApprovalWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalWriter.h) interface.

## Using custom writers

Suppose that you are serialising an object that cannot easily be represented in a text file, such as an image. In this case, the built-in `StringWriter` is not suitable, and you will need to write and use a custom implementation of `ApprovalWriter`. 

Here is a simple example of using a custom writer to produce an HTML file.

<!-- snippet: use_custom_writer -->
<a id='snippet-use_custom_writer'></a>
```cpp
HtmlWriter writer("<h1>hello world</h1>", ".html");
Approvals::verify(writer);
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L11-L14' title='File snippet `use_custom_writer` was extracted from'>snippet source</a> | <a href='#snippet-use_custom_writer' title='Navigate to start of snippet `use_custom_writer`'>anchor</a></sup>
<!-- endSnippet -->

## Using custom filename extensions

Suppose that you are serializing an object in some text format like `JSON` or `CSV`. By writing to this file extension, different tools will render it appropriately.

If all you want to do is change the file extension, here is how:

<!-- snippet: use_custom_file_extension -->
<a id='snippet-use_custom_file_extension'></a>
```cpp
Approvals::verify("<h1>hello world</h1>",
                  Options().fileOptions().withFileExtension(".html"));
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L19-L22' title='File snippet `use_custom_file_extension` was extracted from'>snippet source</a> | <a href='#snippet-use_custom_file_extension' title='Navigate to start of snippet `use_custom_file_extension`'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
