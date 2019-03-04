<!--
This file was generate by the MarkdownSnippets.
Source File: \doc\ToString.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->

# String conversions

When you use Approval tests, the results of the things you are testing are going to be stored on disk. It is good if you can diff the files, to gain an understanding of what is created and how they change. Mainly this is done by creating strings.

## How

This is often done by providing an output operator (`<<`) for types you wish to test.

For example:

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

You should put this function in the same namespace as your type, or the global namespace, and have it declared before including Approval's header. (This is particularly important if you are compiling with Clang.)

If including `<iostream>` or similar is problematic, for example because your code needs be compiled for embedded platforms, and you are tempted to surround it with `#ifdef`s so that it only shows up in testing, we recommend that you use the template approach instead:

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

Wrapper classes or functions can be used to provide additional output formats for types of data:

<!-- snippet: to_string_wrapper_example -->
```cpp
struct FormatRectangleForMultipleLines{

    explicit FormatRectangleForMultipleLines(const Rectangle3& rectangle) : rectangle(rectangle)
    {
    }

    const Rectangle3& rectangle;

    friend std::ostream &operator<<(std::ostream &os, const FormatRectangleForMultipleLines &wrapper) {
        os << "(x,y,width,height) = (" <<
           wrapper.rectangle.x << "," <<
           wrapper.rectangle.y << "," <<
           wrapper.rectangle.width << "," <<
           wrapper.rectangle.height << ")";
        return os;
    }
};

TEST_CASE("AlternativeFormattingCanBeEasyToRead") {
    Approvals::verifyAll(
        "rectangles",
        getRectangles(),
        [](auto r, auto& os){os << FormatRectangleForMultipleLines(r);}
    );
}
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/ToStringWrapperExample.cpp#L37-L63)</sup>
<!-- endsnippet -->

## Design

If your code already has output operators, then go ahead and use them in Approvals.

If your code doesn't have output operators already, then here are some general guidelines to consider, to generate strings that work well with Approvals.

The general design rules when writing:

1. Objects print their relevant data
2. The data is consistent between runs (no times, pointers, random)
3. The data is easy to read

Note: for the same data, different tests might need different string conversions, to satisfy these rules.

Method | Example | Advantages | Disadvantages
------------ | ------------- | ------------- | -------------
XML | `<type> xml </type>` | Works with standard tools | Very verbose; hard to scan by eye
JSON | `{"type":"json"}`  | Works with standard tools; less verbose | &nbsp;
YAML | `type:yaml` | Works with standard tools; less verbose | Indentation matters
simple | `(type: simple)` |   &nbsp;  | It's a custom format
simpler | `(simpler)` | &nbsp; | Does not include meta data
formatted | `(type)=(formatted)` | Works well for many lines of the same type of data, for example an array of rectangles | &nbsp;
tab-separated | &nbsp; | Works with Excel and Markdown; works well for many lines of the same data | &nbsp;
comma-separated | `type, csv` | Works with Excel | Works with Excel

### Composability

TODO Explain things like:

* When are things very non-composable, e.g. hand-coded YAML

### Lists

Notice how this:

<!-- snippet: ApprovalTests_Catch2_Tests/ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt -->
```txt
rectangles


[x: 4 y: 50 width: 100 height: 61]
[x: 50 y: 5200 width: 400 height: 62]
[x: 60 y: 3 width: 7 height: 63]


```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt#L1-L8)</sup>
<!-- endsnippet -->

compares to this:

<!-- snippet: ApprovalTests_Catch2_Tests/ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt -->
```txt
rectangles


(x,y,width,height) = (4,50,100,61)
(x,y,width,height) = (50,5200,400,62)
(x,y,width,height) = (60,3,7,63)


```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt#L1-L8)</sup>
<!-- endsnippet -->

Some formats will be more readable when you are writing lists of objects.

### Tools

TODO Explain things like:

* Using Excel to create graphs
* Loading runt-time data from captured approval results
* Querying logs from JSON output
* IExecutable queries
