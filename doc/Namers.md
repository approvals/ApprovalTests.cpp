<a id="top"></a>

# Namers

<!-- toc -->
## Contents

  * [The Purpose of Namers](#the-purpose-of-namers)
  * [The Parts of Namers](#the-parts-of-namers)
  * [Registering a Custom Namer](#registering-a-custom-namer)
    * [Locally](#locally)
    * [Globally](#globally)
  * [Alternative Namers](#alternative-namers)
    * [TemplatedCustomNamer](#templatedcustomnamer)
      * [Supported tags](#supported-tags)
    * [SeparateApprovedAndReceivedDirectoriesNamer](#separateapprovedandreceiveddirectoriesnamer)
  * [Approving multiple files from one test](#approving-multiple-files-from-one-test)<!-- endToc -->

## The Purpose of Namers

`Approvals::verify(text);`

could be written as:

`REQUIRE(text == (loadContentsFromFile("FileName.TestName.approved.txt"));`

Part of Approval Tests' "Convention over Configuration" is to remove this by automatically creating meaningful file names, and therefore it could be written as:

`REQUIRE(text == (loadContentsFromFile(namer.getApprovedFile()));`

"If you **always** have to do something, you should **never** have to do something."

Since all of your `REQUIRE`s would look like this, we can simplify it with the above `Approvals::verify(text);` - and this is enabled by the ApprovalNamers.

## The Parts of Namers

The conventional layout for files saved with `Approvals::verify()` and related functions is:

* `path_to_test_file/FileName.TestName.approved.txt`
* `path_to_test_file/FileName.TestName.received.txt`

The Approval Namer is responsible for creating these two names.

The interface for this
is [`ApprovalNamer`](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/core/ApprovalNamer.h).

## Registering a Custom Namer

### Locally

If you want to use a specific namer for a specific test, the easiest way is via Options:

<!-- snippet: templated_custom_namer_injection_via_options -->
<a id='snippet-templated_custom_namer_injection_via_options'></a>
```cpp
auto namer = TemplatedCustomNamer::create(
    "{TestSourceDirectory}/CustomName.{ApprovedOrReceived}.{FileExtension}");
Approvals::verify("Hello", Options().withNamer(namer));
```
<sup><a href='/tests/DocTest_Tests/namers/TemplatedCustomNamerTests.cpp#L24-L28' title='Snippet source file'>snippet source</a> | <a href='#snippet-templated_custom_namer_injection_via_options' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### Globally

If you ever want to create a custom namer, that's used in multiple places, Approval Tests has a mechanism to change
which namer it uses by default. Please note that you need to create a function that creates new namers.

<!-- snippet: register_default_namer -->
<a id='snippet-register_default_namer'></a>
```cpp
auto default_namer_disposer =
    Approvals::useAsDefaultNamer([]() { return std::make_shared<FakeNamer>(); });
```
<sup><a href='/tests/DocTest_Tests/namers/NamerTests.cpp#L28-L31' title='Snippet source file'>snippet source</a> | <a href='#snippet-register_default_namer' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Hint:** Many namer classes have a `useAsDefaultNamer()` convenience method to do this for you.

## Alternative Namers

### TemplatedCustomNamer

The easiest way to create a custom namer is to use a `TemplatedCustomNamer`.

Here is an example:

<!-- snippet: templated_custom_namer_example -->
<a id='snippet-templated_custom_namer_example'></a>
```cpp
TemplatedCustomNamer namer("/my/source/directory/{ApprovedOrReceived}/"
                           "{TestFileName}.{TestCaseName}.{FileExtension}");
```
<sup><a href='/tests/DocTest_Tests/namers/TemplatedCustomNamerTests.cpp#L9-L12' title='Snippet source file'>snippet source</a> | <a href='#snippet-templated_custom_namer_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### Supported tags

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


### SeparateApprovedAndReceivedDirectoriesNamer

The pattern used by this class for file names is:

<!-- snippet: separate_approved_and_received_directory_names -->
<a id='snippet-separate_approved_and_received_directory_names'></a>
```cpp
auto path = "{TestSourceDirectory}/{ApprovedOrReceived}/{TestFileName}.{TestCaseName}.{FileExtension}";
```
<sup><a href='/ApprovalTests/namers/SeparateApprovedAndReceivedDirectoriesNamer.cpp#L7-L9' title='Snippet source file'>snippet source</a> | <a href='#snippet-separate_approved_and_received_directory_names' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Which results in these file names:

- `./approved/{TestFileName}.{TestCaseName}.{FileExtension}`
- `./received/{TestFileName}.{TestCaseName}.{FileExtension}`

This layout enables you to use Beyond Compare 4 (or any other directory comparison tool) to do a folder/directory comparison, in order to compare pairs of files in the `approved/` and `received/` directories, and approve one or more files by copying them (without renaming) from `received/` to `approved/`.

The `approved/` and `received/` directories are created automatically.

To register this as your default namer, use:

<!-- snippet: register_separate_directories_namer -->
<a id='snippet-register_separate_directories_namer'></a>
```cpp
auto default_namer_disposer =
    SeparateApprovedAndReceivedDirectoriesNamer::useAsDefaultNamer();
```
<sup><a href='/tests/DocTest_Tests/namers/NamerTests.cpp#L48-L51' title='Snippet source file'>snippet source</a> | <a href='#snippet-register_separate_directories_namer' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

When using this namer, you will want to add the following line to your `.gitignore` file:

```
**/received/
```

## Approving multiple files from one test 

See [MultipleOutputFilesPerTest](/doc/MultipleOutputFilesPerTest.md#top).

---

[Back to User Guide](/doc/README.md#top)
