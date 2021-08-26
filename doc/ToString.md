<a id="top"></a>

# String conversions

<!-- toc -->
## Contents

  * [Introduction](#introduction)
  * [How Approval Tests converts your objects to strings](#how-approval-tests-converts-your-objects-to-strings)
  * [Pass in a string](#pass-in-a-string)
  * [Write a custom std::ostream operator (`<<`)](#write-a-custom-stdostream-operator-)
  * [Specialize StringMaker](#specialize-stringmaker)
    * [gcc 5 & 6](#gcc-5--6)
  * [Use `TApprovals<YourStringConvertingClass>`](#use-tapprovalsyourstringconvertingclass)
  * [See also](#see-also)<!-- endToc -->

## Introduction

When you use Approval tests, any object you pass in is going to be converted to a string. This is how Approval Tests does that, and how you can customize that behavior.

## How Approval Tests converts your objects to strings

The process from your input to the final output looks like this - You can customize the string at any of these 4 points:

1. Input
1. The TApprovals class has a template parameter StringConverter
1. Approvals uses the default StringMaker
1. StringMaker converts via std::ostream operator (<<)

## Pass in a string

Approval Tests can take a string, so it can be simple to simply create that string before you call `verify()`.
This has the advantage of being straight-forward, but won't interact well with calls like `verifyAll()` or Combination Approvals.

## Write a custom std::ostream operator (`<<`)

This is often done by providing an output operator (`<<`) for types you wish to test.

For example:

<!-- snippet: to_string_standard_example -->
<a id='snippet-to_string_standard_example'></a>
```cpp
friend std::ostream& operator<<(std::ostream& os, const Rectangle1& rectangle)
{
    os << "[x: " << rectangle.x << " y: " << rectangle.y
       << " width: " << rectangle.width << " height: " << rectangle.height << "]";
    return os;
}
```
<sup><a href='/tests/DocTest_Tests/docs/ToStringExample.cpp#L11-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-to_string_standard_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

You should put this function in the same namespace as your type, or the global namespace, and have it declared before including Approval's header. (This is particularly important if you are compiling with Clang.)

If including `<iostream>` or similar is problematic, for example because your code needs to be compiled for embedded platforms, and you are tempted to surround it with `#ifdef`s so that it only shows up in testing, we recommend that you use the template approach instead:

<!-- snippet: to_string_template_example -->
<a id='snippet-to_string_template_example'></a>
```cpp
template <class STREAM>
friend STREAM& operator<<(STREAM& os, const Rectangle2& rectangle)
{
    os << "[x: " << rectangle.x << " y: " << rectangle.y
       << " width: " << rectangle.width << " height: " << rectangle.height << "]";
    return os;
}
```
<sup><a href='/tests/DocTest_Tests/docs/ToStringTemplateExample.cpp#L13-L21' title='Snippet source file'>snippet source</a> | <a href='#snippet-to_string_template_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Wrapper classes or functions can be used to provide additional output formats for types of data:

<!-- snippet: to_string_wrapper_example -->
<a id='snippet-to_string_wrapper_example'></a>
```cpp
struct FormatRectangleForMultipleLines
{

    explicit FormatRectangleForMultipleLines(const Rectangle3& rectangle_)
        : rectangle(rectangle_)
    {
    }

    const Rectangle3& rectangle;

    friend std::ostream& operator<<(std::ostream& os,
                                    const FormatRectangleForMultipleLines& wrapper)
    {
        os << "(x,y,width,height) = (" << wrapper.rectangle.x << ","
           << wrapper.rectangle.y << "," << wrapper.rectangle.width << ","
           << wrapper.rectangle.height << ")";
        return os;
    }
};

TEST_CASE("AlternativeFormattingCanBeEasyToRead")
{
    ApprovalTests::Approvals::verifyAll(
        "rectangles", getRectangles(), [](auto r, auto& os) {
            os << FormatRectangleForMultipleLines(r);
        });
}
```
<sup><a href='/tests/DocTest_Tests/docs/ToStringWrapperExample.cpp#L35-L63' title='Snippet source file'>snippet source</a> | <a href='#snippet-to_string_wrapper_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Note** The output operator (`<<`) needs to be declared before Approval Tests. Usually this is handled by putting it in its own header file, and including that at the top of the test source code.

## Specialize StringMaker

If you want to use something other than an output operator (`<<`), one option is to create a specific specialization for StringMaker, for your specific type.

Here is an example:

<!-- snippet: customising_to_string_with_string_maker_specialization -->
<a id='snippet-customising_to_string_with_string_maker_specialization'></a>
```cpp
template <>
std::string ApprovalTests::StringMaker::toString(const StringMakerPrintable& printable)
{
    return "From StringMaker: " + std::to_string(printable.field1_);
}
```
<sup><a href='/tests/DocTest_Tests/CustomizingToStringTests.cpp#L47-L53' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_with_string_maker_specialization' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

### gcc 5 & 6

With older compilers, you might need to make the namespace explicit, like this:

<!-- snippet: customising_to_string_with_string_maker_specialization_gcc5_and_6 -->
<a id='snippet-customising_to_string_with_string_maker_specialization_gcc5_and_6'></a>
```cpp
namespace ApprovalTests
{
    template <> std::string StringMaker::toString(const StringMakerPrintable& printable)
    {
        return "From StringMaker: " + std::to_string(printable.field1_);
    }
}
```
<sup><a href='/tests/DocTest_Tests/CustomizingToStringTests.cpp#L37-L45' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_with_string_maker_specialization_gcc5_and_6' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Use `TApprovals<YourStringConvertingClass>`

If you want to change a broader category of how strings are created, you can create your own string-maker class,
and tell Approvals to use it, using the template mechanism.

Here is how you create your own string-maker class:

<!-- snippet: customising_to_string_with_custom_to_string_class -->
<a id='snippet-customising_to_string_with_custom_to_string_class'></a>
```cpp
class CustomToStringClass
{
public:
    template <typename T> static std::string toString(const T& printable)
    {
        return "From Template: " + std::to_string(printable.field1_);
    }
};
```
<sup><a href='/tests/DocTest_Tests/CustomizingToStringTests.cpp#L79-L88' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_with_custom_to_string_class' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

However, this alone will not do anything. You now need to call a variation of Approvals that uses it.
You can do this directly by:

<!-- snippet: customising_to_string_with_custom_to_string_class_usage1 -->
<a id='snippet-customising_to_string_with_custom_to_string_class_usage1'></a>
```cpp
ApprovalTests::TApprovals<
    ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>::verify(p);
```
<sup><a href='/tests/DocTest_Tests/CustomizingToStringTests.cpp#L95-L98' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_with_custom_to_string_class_usage1' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Or you can create your own custom alias to use your customisation:

<!-- snippet: customising_to_string_with_custom_to_string_class_usage2 -->
<a id='snippet-customising_to_string_with_custom_to_string_class_usage2'></a>
```cpp
using MyApprovals = ApprovalTests::TApprovals<
    ApprovalTests::ToStringCompileTimeOptions<CustomToStringClass>>;

MyApprovals::verify(p);
```
<sup><a href='/tests/DocTest_Tests/CustomizingToStringTests.cpp#L107-L112' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_with_custom_to_string_class_usage2' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

With `MyApprovals::verify()`, we have not changed the behavior of `Approvals::verify()`.

If, instead, you want to change the default string formatting, so that all calls to `Approvals::verify()` and related methods will automatically use your new string formatter, you can override the default, by defining this macro **before including the Approval Tests header**.

<!-- snippet: customising_to_string_default_converter -->
<a id='snippet-customising_to_string_default_converter'></a>
```h
#define APPROVAL_TESTS_DEFAULT_STREAM_CONVERTER StringMaker
```
<sup><a href='/ApprovalTests/Approvals.h#L251-L253' title='Snippet source file'>snippet source</a> | <a href='#snippet-customising_to_string_default_converter' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## See also

* [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top)
* [How to Scrub Non-Deterministic Output](/doc/how_tos/ScrubNonDeterministicOutput.md#top)
* [How to Use the Fmt Library To Print Objects](/doc/how_tos/UseTheFmtLibraryToPrintObjects.md#top).

---

[Back to User Guide](/doc/README.md#top)
