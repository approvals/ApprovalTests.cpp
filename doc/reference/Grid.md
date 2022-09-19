<a id="top"></a>

# Grid

<!-- toc -->
## Contents

  * [What it is](#what-it-is)
  * [Where is this useful?](#where-is-this-useful)
  * [Usage](#usage)
    * [Conventional Usage](#conventional-usage)
    * [Simple Starting Point](#simple-starting-point)<!-- endToc -->

## What it is

A utility for creating 2D text in a grid format.
Grid abstracts away the printing of the grid, so you can focus on how to represent the contents of each cell.

## Where is this useful?

1. When you want to visualize the contents of 2 dimensional data, (usually for verification purposes).
1. When trying to print/verify Board games, Puzzles & 2D Video games that are based on some kind of grid

## Usage 

### Conventional Usage

Grid is passed a width, height, and a function pointer or lambda to represent the contents of each cell. 

For example:

<!-- snippet: grid_lambda -->
<a id='snippet-grid_lambda'></a>
```cpp
auto grid = ApprovalTests::Grid::print(
    4, 3, [](int x, int y, auto& os) { os << "(" << x << "," << y << ") "; });
```
<sup><a href='/tests/DocTest_Tests/utilities/GridTests.cpp#L21-L24' title='Snippet source file'>snippet source</a> | <a href='#snippet-grid_lambda' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

which produces:

<!-- snippet: GridTests.Print_Coordinates.approved.txt -->
<a id='snippet-GridTests.Print_Coordinates.approved.txt'></a>
```txt
(0,0) (1,0) (2,0) (3,0) 
(0,1) (1,1) (2,1) (3,1) 
(0,2) (1,2) (2,2) (3,2)
```
<sup><a href='/tests/DocTest_Tests/utilities/approval_tests/GridTests.Print_Coordinates.approved.txt#L1-L4' title='Snippet source file'>snippet source</a> | <a href='#snippet-GridTests.Print_Coordinates.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Notice how `Grid::print()` removes the need for looping over `x` & `y`.

### Simple Starting Point

When developing with [Fake it till you make it](/doc/Glossary.md#fake-it-till-you-make-it) Grid can be used to start by printing a simple grid of repeating text, such as:

<!-- snippet: grid_simple -->
<a id='snippet-grid_simple'></a>
```cpp
auto grid = ApprovalTests::Grid::print(4, 2, ".");
```
<sup><a href='/tests/DocTest_Tests/utilities/GridTests.cpp#L13-L15' title='Snippet source file'>snippet source</a> | <a href='#snippet-grid_simple' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

which produces:

<!-- snippet: GridTests.Print_Simple.approved.txt -->
<a id='snippet-GridTests.Print_Simple.approved.txt'></a>
```txt
....
....
```
<sup><a href='/tests/DocTest_Tests/utilities/approval_tests/GridTests.Print_Simple.approved.txt#L1-L3' title='Snippet source file'>snippet source</a> | <a href='#snippet-GridTests.Print_Simple.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

which you can then build on by gradually implementing your lambda...

---

[Back to User Guide](/doc/README.md#top)
