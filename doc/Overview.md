<a id="top"></a>

# Overview of Approval Tests

<!-- toc -->
## Contents

  * [Summary](#summary)
  * [Traditional Asserts](#traditional-asserts)
  * [Approval Tests](#approval-tests)<!-- endToc -->

## Summary

Approval Tests are an alternative to writing expression assertions in your code.

As the following examples demonstrate, Approval Tests can result in significantly simpler and more elegant tests of complex objects.

## Traditional Asserts

Traditional tests spend equal time focusing on creating the inputs and verifying the outputs. 

When the objects being tested are non-trivial, either the tests become quite verbose (as shown in this example), or it's tempting to only test a small part of the behaviour.

<!-- snippet: sandwich_example_with_requires -->
<a id='snippet-sandwich_example_with_requires'></a>
```cpp
// Arrange, Act
Sandwich s = createSandwichForTest();
// Assert
REQUIRE("Sourdough" == s.getBread());
REQUIRE(s.getCondiments().contains("Mayo"));
REQUIRE(s.getCondiments().contains("Pepper"));
REQUIRE(s.getCondiments().contains("Olive Oil"));
REQUIRE(s.getFillings().contains("Tomato"));
REQUIRE(s.getFillings().contains("Lettuce"));
REQUIRE(s.getFillings().contains("Cheddar"));
```
<sup><a href='/tests/DocTest_Tests/docs/OverviewExamples.cpp#L86-L97' title='Snippet source file'>snippet source</a> | <a href='#snippet-sandwich_example_with_requires' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Approval Tests

Approval Tests simplify the verification of outputs. They do this by writing the outputs to a file, which once saved, becomes your spec.

You still supply the inputs, but Approval Tests gives you [powerful ways of viewing complex outputs](/doc/Reporters.md#top), meaning you can move on to the next feature or next test more quickly.

<!-- snippet: sandwich_example_with_approvals -->
<a id='snippet-sandwich_example_with_approvals'></a>
```cpp
// Arrange, Act
Sandwich s = createSandwichForTest();
// Assert
ApprovalTests::Approvals::verify(s);
```
<sup><a href='/tests/DocTest_Tests/docs/OverviewExamples.cpp#L102-L107' title='Snippet source file'>snippet source</a> | <a href='#snippet-sandwich_example_with_approvals' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This generates the approval file - which is generated **for** you, but [approved **by** you](/doc/ApprovingResults.md#top).

<!-- snippet: OverviewExamples.SandwichExampleWithApprovals.approved.txt -->
<a id='snippet-OverviewExamples.SandwichExampleWithApprovals.approved.txt'></a>
```txt
sandwich {
    bread: "Sourdough",
    condiments: ["Mayo", "Pepper", "Olive Oil"],
    fillings: ["Tomato", "Lettuce", "Cheddar"]
}
```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/OverviewExamples.SandwichExampleWithApprovals.approved.txt#L1-L5' title='Snippet source file'>snippet source</a> | <a href='#snippet-OverviewExamples.SandwichExampleWithApprovals.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
