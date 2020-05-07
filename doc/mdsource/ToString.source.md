<a id="top"></a>

# String conversions


toc

## Introduction

When you use Approval tests, any object you pass in is going to be converted to a string. This is how Approval Tests does that, and how you can customize that behavior.

## How Approval Tests converts your objects to strings

The process from your input to the final output looks like:

1. Input
1. The TApprovals class has a template parameter StringConverter
1. Approvals uses the default StringMaker
1. StringMaker converts via std::ostream operator (<<)

You can customize the string at any of these 4 points. 

## Pass in a string

Approval Tests can take a string, so it can be simple to simply create that string before you call `verify()`.
This has the advantage of being straight-forward, but won't interact well with calls like `verifyAll()` or Combination Approvals.

## Write a custom std::ostream operator (`<<`)

This is often done by providing an output operator (`<<`) for types you wish to test.

For example:

snippet: to_string_standard_example

You should put this function in the same namespace as your type, or the global namespace, and have it declared before including Approval's header. (This is particularly important if you are compiling with Clang.)

If including `<iostream>` or similar is problematic, for example because your code needs be compiled for embedded platforms, and you are tempted to surround it with `#ifdef`s so that it only shows up in testing, we recommend that you use the template approach instead:

snippet: to_string_template_example

Wrapper classes or functions can be used to provide additional output formats for types of data:

snippet: to_string_wrapper_example

**Note** The output operator (`<<`) needs to be declared before Approval Tests. Usually this is handled by putting it in its own header file, and including that at the top of the test source code.

## Specialize StringMaker

If you want to use something other than an output operator (`<<`), one option is to create a specific specialization for StringMaker, for your specific type.

Here is an example:

snippet: customising_to_string_with_string_maker_specialization

## Use `TApprovals<YourStringConvertingClass>`

If you want to change a broader category of how strings are created, you can create your own string-maker class,
and tell Approvals to use it, using the template mechanism.

Here is how you create your own string-maker class:

snippet: customising_to_string_with_custom_to_string_class

However, this alone will not do anything. You now need to call a variation of Approvals that uses it.
You can do this directly by:

snippet: customising_to_string_with_custom_to_string_class_usage1

Or you can override the default Approvals template to use your customisation:

snippet: customising_to_string_with_custom_to_string_class_usage2

Or you can change the default, by defining this macro before including the Approval Tests header.

snippet: customising_to_string_default_converter

## See also

* [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top)



---

[Back to User Guide](/doc/README.md#top)
