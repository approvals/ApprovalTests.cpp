<a id="top"></a>

# Tips for Designing Strings


toc


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

snippet: verify_list

Notice how this:

snippet: ToStringWrapperExample.MultipleLinesCanBeHardToRead.approved.txt

compares to this:

snippet: ToStringWrapperExample.AlternativeFormattingCanBeEasyToRead.approved.txt

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
