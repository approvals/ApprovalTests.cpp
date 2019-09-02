<a id="top"></a>

# Writers

toc

## Default Behaviour

By default, when Approval Tests verifies an object, it uses the [StringWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/writers/StringWriter.h) class to write out the string representation of the object.

And by default, `StringWriter` gives the saved file the extension `.txt`. 

`StringWriter` implements the [ApprovalWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalWriter.h) interface.

## Using custom writers

Suppose that you are serialising an object that cannot easily be represented in a text file, such as an image. In this case, the built-in `StringWriter` is not suitable, and you will need to write and use a custom implementation of `ApprovalWriter`. 

Here is a simple example of using a custom writer to produce an HTML file.

snippet: use_custom_writer

## Using custom filename extensions

Suppose that you are serializing an object in some text format like `JSON` or `CSV`. By writing to this file extension, different tools will render it appropriately.

If all you want to do is change the file extension, there are many convenience functions to enable this, for example:

snippet: use_custom_file_extension 

---

[Back to User Guide](/doc/README.md#top)
