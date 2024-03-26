<a id="top"></a>

# Testing Combinations

<!-- toc -->
## Contents

  * [When to use Combinations](#when-to-use-combinations)
  * [Steps](#steps)
  * [The Basics](#the-basics)
    * [Passing in a Reporter](#passing-in-a-reporter)
  * [C++ Language Versions](#c-language-versions)<!-- endToc -->

## When to use Combinations

You have a function that takes, for example, 3 parameters, and you want to test its behaviour with a bunch of different values for each of those parameters.

If you have only one parameter that you want to vary, check out [How to Test a Variety of Values for One Input](/doc/how_tos/TestAVarietyOfValues.md#top).

## Steps

1. Copy this starter text, and adjust for the number of inputs that you have.

<!-- snippet: CombinationsStartingPoint -->
<a id='snippet-CombinationsStartingPoint'></a>
```cpp
TEST_CASE("CombinationsStartingPoint")
{
    std::vector<std::string> inputs1{"input1.value1", "input1.value2"};
    std::vector<std::string> inputs2{"input2.value1", "input2.value2", "input2.value3"};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        "TITLE",
        [&](auto /*input1*/, auto /*input2*/) { return "placeholder"; },
        inputs1,
        inputs2);
}
```
<sup><a href='/tests/DocTest_Tests/CombinationExamples.cpp#L20-L31' title='Snippet source file'>snippet source</a> | <a href='#snippet-CombinationsStartingPoint' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

2. Modify each input container for your chosen values.
3. Make sure each input type can be converted to a string (See [To String](/doc/ToString.md#how))
4. Run it, and make sure that you have your inputs wired up correctly.

If they are wired up correctly, you will see a file that looks like this: it is the left hand side of the file that
matters at this point: all combinations of your own input values should be listed:

<!-- snippet: CombinationExamples.CombinationsStartingPoint.approved.txt -->
<a id='snippet-CombinationExamples.CombinationsStartingPoint.approved.txt'></a>
```txt
TITLE


(input1.value1, input2.value1) => placeholder
(input1.value1, input2.value2) => placeholder
(input1.value1, input2.value3) => placeholder
(input1.value2, input2.value1) => placeholder
(input1.value2, input2.value2) => placeholder
(input1.value2, input2.value3) => placeholder
```
<sup><a href='/tests/DocTest_Tests/approval_tests/CombinationExamples.CombinationsStartingPoint.approved.txt#L1-L10' title='Snippet source file'>snippet source</a> | <a href='#snippet-CombinationExamples.CombinationsStartingPoint.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

5. Implement the body of your lambda
6. Make sure that your lambda's return value also has an ostream operator<<
7. Change the TITLE to something meaningful
8. Run it, and approve the output.

## The Basics

You can use `CombinationApprovals::verifyAllCombinations` to test the content of multiple containers.

This makes a kind of approval test matrix, automatically testing all combinations of a set of inputs. It's a powerful way to quickly get very good test coverage.

In this small example, all combinations of `{"hello", "world"}` and `{1, 2, 3}` are being used:

<!-- snippet: YouCanVerifyCombinationsOf2 -->
<a id='snippet-YouCanVerifyCombinationsOf2'></a>
```cpp
TEST_CASE("YouCanVerifyCombinationsOf2")
{
    std::vector<std::string> v{"hello", "world"};
    std::vector<int> numbers{1, 2, 3};
    ApprovalTests::CombinationApprovals::verifyAllCombinations(
        [](std::string s, int i) {
            return std::string("(") + s + ", " + std::to_string(i) + ")";
        },
        v,
        numbers);
}
```
<sup><a href='/tests/DocTest_Tests/CombinationExamples.cpp#L6-L18' title='Snippet source file'>snippet source</a> | <a href='#snippet-YouCanVerifyCombinationsOf2' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

The format is carefully chosen to show both inputs and outputs, to make the test results easy to interpret. The output looks like this:

<!-- snippet: CombinationExamples.YouCanVerifyCombinationsOf2.approved.txt -->
<a id='snippet-CombinationExamples.YouCanVerifyCombinationsOf2.approved.txt'></a>
```txt
(hello, 1) => (hello, 1)
(hello, 2) => (hello, 2)
(hello, 3) => (hello, 3)
(world, 1) => (world, 1)
(world, 2) => (world, 2)
(world, 3) => (world, 3)
```
<sup><a href='/tests/DocTest_Tests/approval_tests/CombinationExamples.YouCanVerifyCombinationsOf2.approved.txt#L1-L7' title='Snippet source file'>snippet source</a> | <a href='#snippet-CombinationExamples.YouCanVerifyCombinationsOf2.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

For advice on effective formatting, see [Tips for Designing Strings](/doc/explanations/TipsForDesigningStrings.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

### Passing in a Reporter

Note: Over releases, the position of the optional Reporter parameter to `verifyAllCombinations` has changed, as the code has evolved:

| Release  | Position of optional Reporter argument |
|----------|---------------------|
| Before v.6.0.0 | The optional Reporter argument goes after all the inputs |
| In v.6.0.0 | The optional Reporter argument should be the **second** argument. |
| After v.6.0.0 | The optional Reporter argument should be the **first** argument. |
| After v.8.7.0 | Reporter is now stored in [Options](/doc/Options.md#top), which should be the **first** argument. |

See:

* [v.6.0.0 release notes](https://github.com/approvals/ApprovalTests.cpp/releases/tag/v.6.0.0)
* [v.7.0.0 release notes](https://github.com/approvals/ApprovalTests.cpp/releases/tag/v.7.0.0)

## C++ Language Versions

If you are using C++11, you will need to supply the exact parameter types to your lambda:

<!-- snippet: sample_combinations_of_three -->
<a id='snippet-sample_combinations_of_three'></a>
```cpp
ApprovalTests::CombinationApprovals::verifyAllCombinations(
    [](const std::string& input1, const int input2, const double input3) {
        return functionThatReturnsSomethingOutputStreamable(input1, input2, input3);
    }, // This is the converter function
    listOfInput1s,
    listOfInput2s,
    listOfInput3s);
```
<sup><a href='/tests/DocTest_Tests/docs/CombinationsSampleCode.cpp#L21-L29' title='Snippet source file'>snippet source</a> | <a href='#snippet-sample_combinations_of_three' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

If you are using C++14 or above, you can simplify this by using `auto` or `auto&` for the lambda parameters:

<!-- snippet: sample_combinations_of_three_with_auto -->
<a id='snippet-sample_combinations_of_three_with_auto'></a>
```cpp
ApprovalTests::CombinationApprovals::verifyAllCombinations(
    [](auto& input1, auto& input2, auto& input3) {
        return functionThatReturnsSomethingOutputStreamable(input1, input2, input3);
    }, // This is the converter function
    listOfInput1s,
    listOfInput2s,
    listOfInput3s);
```
<sup><a href='/tests/DocTest_Tests/docs/CombinationsSampleCode.cpp#L38-L46' title='Snippet source file'>snippet source</a> | <a href='#snippet-sample_combinations_of_three_with_auto' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

---

[Back to User Guide](/doc/README.md#top)
