<a id="top"></a>

# How to Test a Variety of Values for One Input

<!-- toc -->
## Contents

  * [When to use Approvals::verifyAll()](#when-to-use-approvalsverifyall)
  * [Steps](#steps)
  * [Further Advice](#further-advice)<!-- endToc -->

## When to use Approvals::verifyAll()

When you want to test a lot of variations for a single input value.

If you have more than parameter that you want to vary, check out [Testing Combinations](/doc/TestingCombinations.md#top).

## Steps

1. Copy this starter text.

<!-- snippet: VerifyAllStartingPoint -->
<a id='snippet-VerifyAllStartingPoint'></a>
```cpp
TEST_CASE("VerifyAllStartingPoint")
{
    std::vector<std::string> inputs{"input.value1", "input.value2"};
    ApprovalTests::Approvals::verifyAll("TITLE", inputs, [](auto input, auto& stream) {
        stream << input << " => "
               << "placeholder";
    });
}
```
<sup><a href='/tests/DocTest_Tests/VectorTests.cpp#L44-L53' title='Snippet source file'>snippet source</a> | <a href='#snippet-VerifyAllStartingPoint' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

2. Modify the input container for your chosen values.
3. Run it, and make sure that you have your inputs wired up correctly.

If they are wired up correctly, you will see a file that looks like this: it is the left hand side of the file that matters at this point: all combinations of your own input values should be listed:

<!-- snippet: VectorTests.VerifyAllStartingPoint.approved.txt -->
<a id='snippet-VectorTests.VerifyAllStartingPoint.approved.txt'></a>
```txt
TITLE


input.value1 => placeholder
input.value2 => placeholder
```
<sup><a href='/tests/DocTest_Tests/approval_tests/VectorTests.VerifyAllStartingPoint.approved.txt#L1-L6' title='Snippet source file'>snippet source</a> | <a href='#snippet-VectorTests.VerifyAllStartingPoint.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

4. Replace the "placeholder" with a call to the functionality that you want to test.
5. Change the TITLE to something meaningful
6. Run it, and approve the output.

## Further Advice

For advice on effective formatting, see [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

---

[Back to User Guide](/doc/README.md#top)
