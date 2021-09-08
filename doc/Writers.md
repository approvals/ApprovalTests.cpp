<a id="top"></a>

# Writers

<!-- toc -->
## Contents

  * [Default Behaviour](#default-behaviour)
  * [Using custom writers](#using-custom-writers)
  * [Using custom filename extensions](#using-custom-filename-extensions)
  * [Empty Files](#empty-files)
    * [Customizing by File Extension](#customizing-by-file-extension)
    * [Full Customization](#full-customization)<!-- endToc -->

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
ApprovalTests::Approvals::verify(writer);
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L9-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_writer' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Using custom filename extensions

Suppose that you are serializing an object in some text format like `JSON` or `CSV`. By writing to this file extension, different tools will render it appropriately.

If all you want to do is change the file extension, here is how:

<!-- snippet: use_custom_file_extension -->
<a id='snippet-use_custom_file_extension'></a>
```cpp
ApprovalTests::Approvals::verify(
    "<h1>hello world</h1>",
    ApprovalTests::Options().fileOptions().withFileExtension(".html"));
```
<sup><a href='/tests/DocTest_Tests/DocTestApprovalTestTests.cpp#L17-L21' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_custom_file_extension' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->


## Empty Files

Most reporters will create a `.approved.` file if one does not exist, as most diff tools do not handle a missing file well.
By default, these empty files are empty text files with an empty string `""`.

If the file extension is not a text file (for example, a PNG), you will still get this behaviour, which can result in some diff tools saying 'this is not a valid file'.

ApprovalTests allows for you to customize this behaviour.

For a tool which will help you with this, see [EmptyFiles](https://github.com/VerifyTests/EmptyFiles).

### Customizing by File Extension

To add new behaviour for a specific file extension, you can register customizations as follows: 

<!-- snippet: register_html_creator -->
<a id='snippet-register_html_creator'></a>
```cpp
ApprovalTests::EmptyFileCreator htmlCreator = [](std::string fileName) {
    ApprovalTests::StringWriter s("<!doctype html><title>TITLE</title>");
    s.write(fileName);
};
ApprovalTests::EmptyFileCreatorByType::registerCreator(".html", htmlCreator);
```
<sup><a href='/tests/DocTest_Tests/utilities/FileUtilsExamples.cpp#L26-L32' title='Snippet source file'>snippet source</a> | <a href='#snippet-register_html_creator' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This will leave the creation of files with all other extensions alone, and will last for the remainder of program execution, or until a new creator for this file extension is registered.

### Full Customization

Here is an example of replacing the entire empty file creation code, for the lifetime of the disposer.

New `.approved.` files will be created with minimal, valid HTML content, and everything else will be empty.

<!-- snippet: use_empty_file_creator -->
<a id='snippet-use_empty_file_creator'></a>
```cpp
ApprovalTests::EmptyFileCreator htmlCreator = [](std::string fileName) {
    std::string contents = "";
    if (ApprovalTests::StringUtils::endsWith(fileName, ".html"))
    {
        contents = "<!doctype html><title>TITLE</title>";
    }
    ApprovalTests::StringWriter s(contents);
    s.write(fileName);
};
auto disposer = ApprovalTests::FileUtils::useEmptyFileCreator(htmlCreator);
```
<sup><a href='/tests/DocTest_Tests/utilities/FileUtilsExamples.cpp#L10-L21' title='Snippet source file'>snippet source</a> | <a href='#snippet-use_empty_file_creator' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
