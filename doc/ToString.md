<!--
This file was generate by the MarkdownSnippets.
Source File: \doc\ToString.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->

# String conversions

When you use Approval tests, the results of the things you are testing are going to be stored on disk. It is good if you can diff the files, to gain an understanding of what is created and how they change. Mainly this is done by creating strings.

## How

This is often done by overloading the output operator (`<<`).

For example

<!-- snippet: to_string_standard_example -->
```cpp
friend std::ostream &operator<<(std::ostream &os, const Rectangle2 &rectangle) {
    os << "[x: " << rectangle.x << " y: " << rectangle.y << " width: " << rectangle.width << " height: "
       << rectangle.height << "]";
    return os;
}
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/ToStringExample.cpp#L12-L18)</sup>
<!-- endsnippet -->

If including the standard string is problematic, and you are tempted to surround it with `#ifdef`s so that it only shows up in testing, we recommend that you use the template approach instead.

<!-- snippet: to_string_template_example -->
```cpp
template <class STREAM>
friend STREAM &operator<<(STREAM &os, const Rectangle2 &rectangle) {
    os << "[x: " << rectangle.x << " y: " << rectangle.y << " width: " << rectangle.width << " height: "
       << rectangle.height << "]";
    return os;
}
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/ToStringTemplateExample.cpp#L12-L19)</sup>
<!-- endsnippet -->


## Design
