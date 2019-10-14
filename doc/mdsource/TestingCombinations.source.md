<a id="top"></a>

# Testing Combinations

You can use `CombinationApprovals::verifyAllCombinations` to test the content of multiple containers.

This makes a kind of approval test matrix, automatically testing all combinations of a set of inputs. It's a powerful way to quickly get very good test coverage.

In this small example, all combinations of `{"hello", "world"}` and `{1, 2, 3}` are being used:

snippet: YouCanVerifyCombinationsOf2

The format is carefully chosen to show both inputs and outputs, to make the test results easy to interpret. The output looks like this:

snippet: CombinationTests.YouCanVerifyCombinationsOf2.approved.txt

For advice on effective formatting, see [To String](/doc/ToString.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

## Code samples

snippet: sample_combinations_of_three

---

[Back to User Guide](/doc/README.md#top)
