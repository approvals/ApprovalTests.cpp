<a id="top"></a>

# Testing Combinations

toc

## The Basics

You can use `CombinationApprovals::verifyAllCombinations` to test the content of multiple containers.

This makes a kind of approval test matrix, automatically testing all combinations of a set of inputs. It's a powerful way to quickly get very good test coverage.

In this small example, all combinations of `{"hello", "world"}` and `{1, 2, 3}` are being used:

snippet: YouCanVerifyCombinationsOf2

The format is carefully chosen to show both inputs and outputs, to make the test results easy to interpret. The output looks like this:

snippet: CombinationTests.YouCanVerifyCombinationsOf2.approved.txt

For advice on effective formatting, see [To String](/doc/ToString.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

### Passing in a Reporter

Note: Because of the limitations of C++, the Reporter is not optional at the end, as in the rest of Approval Tests. Instead, you can optionally add a Reporter as the second argument.

## Code samples

snippet: sample_combinations_of_three

If you are using C++14 or above, you can simplify this by using `auto` or `auto&` for the lambda parameters:

snippet: sample_combinations_of_three_with_auto

---

[Back to User Guide](/doc/README.md#top)
