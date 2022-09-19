<a id="top"></a>

# Tips for Designing Strings

<!-- toc -->
## Contents

  * [Design](#design)
  * [Composability](#composability)
  * [Lists](#lists)
  * [Tools](#tools)
  * [How to Implement This](#how-to-implement-this)<!-- endToc -->

When you use Approval tests, the results of the things you are testing are going to be stored on disk. It is good if you can diff the files, to gain an understanding of what is created and how they change. Mainly this is done by creating strings.

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

## Composability

TODO Explain things like:

* When are things very non-composable, e.g. hand-coded YAML

## Lists

Some formats will be more readable when you are writing lists of objects.
Here's an example of verifing a list of rectangles

<!-- snippet: verify_list -->
<a id='snippet-verify_list'></a>
```cpp
ApprovalTests::Approvals::verifyAll("rectangles", getRectangles());
```
<sup><a href='/tests/DocTest_Tests/docs/ToStringWrapperExample.cpp#L30-L32' title='Snippet source file'>snippet source</a> | <a href='#snippet-verify_list' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Notice how this:

<!-- snippet: ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt -->
<a id='snippet-ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt'></a>
```txt
rectangles


[0] = [x: 4 y: 50 width: 100 height: 61]
[1] = [x: 50 y: 5200 width: 400 height: 62]
[2] = [x: 60 y: 3 width: 7 height: 63]
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

compares to this:

<!-- snippet: ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt -->
<a id='snippet-ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt'></a>
```txt
rectangles


(x,y,width,height) = (4,50,100,61)
(x,y,width,height) = (50,5200,400,62)
(x,y,width,height) = (60,3,7,63)
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Tools

TODO Explain things like:

* Using Excel to create graphs
* Loading run-time data from captured approval results
* Querying logs from JSON output
* IExecutable queries

## How to Implement This

Approvals offers multiple ways to customise the To String. For details,
see [String conversions](/doc/ToString.md#top).

---

[Back to User Guide](/doc/README.md#top)
