<a id="top"></a>

# Writers

toc

## Default Behaviour

By default, when Approval Tests verifies an object, it uses the [StringWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/writers/StringWriter.h) class to write out the string representation of the object.

And by default, `StringWriter` gives the saved file the extension `.txt`. 

`StringWriter` implements the [ApprovalWriter](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalWriter.h) interface.

## Using custom writers

Suppose that you are serialising an object that cannot easily be represented in a text file, such as an image. In this case, the built-in `StringWriter` is not suitable, and you will need to write and use a custom implementation of `ApprovalWriter`. 

There is not yet a way to customise the default `ApprovalWriter`.

This means that if you need to use a custom writer, you will need to call the low-level [`FileApprover::verify(ApprovalNamer, ApprovalWriter, Reporter)`](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/FileApprover.h)
method, for example:

<!-- todo: Clare has shelved example code for this - which can be committed after expected, conflicting pull-requests are merged. -->

```cpp
MyCustomWriter writer(object);
FileApprover::verify(*Approvals::getDefaultNamer(), writer, DefaultReporter());
```

Unfortunately this absence of a customization point for writers means that the following are not yet available for use with custom writers:

* `Approvals::verify()`
* `Approvals::verifyAll()`
* `CombinationApprovals::verifyAllCombinations()`)

## Using custom filename extensions

Suppose that you are serializing an object in some text format like `JSON` or `CSV`, and you would like your chosen [Reporter](/doc/Reporters.md#top) to detect the file name extension, in order to give nice syntax-highlighting when reviewing diffs.

The default file name extension for Approval files is `.txt`. When using the standard verification methods, the filename extension cannot currently be changed.

<!-- todo: Clare has shelved example code for these - which can be committed after expected, conflicting pull-requests are merged. -->

Currently, the only ways to modify the filename extensions of Approved and Received files are quite specialised:

**Either:** Write the received file yourself, and then use `Approvals::verifyExistingFile()` to verify it.

```cpp
const std::string text = "1,2,3,4";

const std::string extensionWithDot(".tsv");
StringWriter writer(text, extensionWithDot);

const std::string receivedFile =
    Approvals::getDefaultNamer()->getReceivedFile(extensionWithDot);
writer.write(receivedFile);

Approvals::verifyExistingFile(receivedFile);
// Note: verifyExistingFile() does not remove the received file when the test passes
```

**Or:** Call `FileApprover::verify(ApprovalNamer, ApprovalWriter, Reporter)` and pass in a `StringWriter` you've supplied an extension to, e.g. `StringWriter(".tsv")`, for example:

```cpp
std::string text = "1,2,3,4";
StringWriter writer(text, ".tsv");
FileApprover::verify( *Approvals::getDefaultNamer(), writer, DefaultReporter() );
```

---

[Back to User Guide](/doc/README.md#top)
