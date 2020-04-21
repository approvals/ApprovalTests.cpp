<a id="top"></a>

# Why We Are Converting To Options

toc

## First Section Here

2020-04-21

With the addition of Scrubbers, we realised that ApprovalTests has some optional parameters. The only one we had of these before was reporter. Because of that, we decided to group together all of the options in to a single container object. This gives us a few advantages:

1. We can expand in the future without changing the API.
2. Adding functionality becomes simpler, because it passes through to a single place.

It is effectively preparing to use the "Introduce Parameter Object" refactoring pattern.

## API

Our current pattern is to have an optional Reporter at the end of any verify() method.

We are switching this to have an option Options object instead.

This temporarily doubles our API interface, and we are deprecating the Reporter overloads.
When enabled, these deprecation warnings will show up as:
 
* compiler C++14 and above, using the `[[deprecated("..."]]` feature
* messages on std::cout in C++11

Our plan is to:
 
* start with the deprecations being something users can opt in to
* deprecation warnings are opt-out
* deprecation warnings are forced
* the deprecated methods are removed

## Opting in 

Currently (2020-04-21), warnings when using the old interface are turned off. To see them, add this line of code in your C++ code: 

snippet: show_deprecation_warnings

Or this to your CMakeLists.txt:

snippet: show_deprecation_warnings_cmake

---

[Back to User Guide](/doc/README.md#top)
