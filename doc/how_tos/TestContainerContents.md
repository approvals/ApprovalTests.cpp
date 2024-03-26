<a id="top"></a>

# How to Test the Contents of a Container

<!-- toc -->
## Contents

  * [When to test a container](#when-to-test-a-container)
  * [Steps](#steps)
  * [More Examples](#more-examples)
  * [Further Advice](#further-advice)<!-- endToc -->

## When to test a container

You have called a method that returns a collection of objects, and you want a nicer read-out than the standard verify() will give you.

## Steps

1. Copy this starter text.

<!-- snippet: VerifyAllStartingPointContainer -->
<a id='snippet-VerifyAllStartingPointContainer'></a>
```cpp
std::vector<std::string> objectsToVerify{"hello", "world"};
ApprovalTests::Approvals::verifyAll("TITLE", objectsToVerify);
```
<sup><a href='/tests/DocTest_Tests/VectorTests.cpp#L27-L30' title='Snippet source file'>snippet source</a> | <a href='#snippet-VerifyAllStartingPointContainer' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

which would produce:

<!-- snippet: VectorTests.YouCanVerifyVectorsWithStandardText.approved.txt -->
<a id='snippet-VectorTests.YouCanVerifyVectorsWithStandardText.approved.txt'></a>
```txt
TITLE


[0] = hello
[1] = world
```
<sup><a href='/tests/DocTest_Tests/approval_tests/VectorTests.YouCanVerifyVectorsWithStandardText.approved.txt#L1-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-VectorTests.YouCanVerifyVectorsWithStandardText.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

2. Replace the `objectsToVerify` container with your collection of objects.
3. Change the TITLE to something meaningful
4. Run it, and approve the output.

## More Examples

For some examples, see [VectorTests.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/VectorTests.cpp).

## Further Advice

For advice on effective formatting, see [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

---

[Back to User Guide](/doc/README.md#top)
