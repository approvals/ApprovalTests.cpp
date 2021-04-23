<a id="top"></a>

# ApprovalTesting (the concept)

<!-- toc -->
## Contents

  * [The Idea](#the-idea)
  * [The Path](#the-path)
    * [1 Simple verification](#1-simple-verification)
      * [The technique](#the-technique)
      * [The problem](#the-problem)
    * [2 ToString verification](#2-tostring-verification)
      * [The technique](#the-technique-1)
      * [The problem](#the-problem-1)<!-- endToc -->

This is also referred to as snapshot testing, or golden master testing.

## The Idea
Most tests have you explicitly state what is expected before you write the code,
ApprovalTesting, instead has you state the data you are interested in checking,
has you manually check it until you decide you are satisfied and then continues
to ensure it remains consistent for the future.

ApprovalTesting also harnesses the power of other tools to make
the results, and the differences in results, easier to understand and act on.

## The Path

### 1 Simple verification

#### The technique

Most of us are familiar with simple checks for numbers or strings.
```cpp
REQUIRE( 1 == count);
REQUIRE( "Clare" == name);
```

#### The problem
But this can get complicated if you have a large list or object with many fields.
```cpp
REQUIRE( "Clare" == names[0]);
REQUIRE( "Llewellyn" == names[1]);
REQUIRE( "Simon" == names[2]);
REQUIRE( "James" == names[3]);
REQUIRE( "Emily" == names[4]);
```

One solution for this is to start writing objects to string that are easier to verify.

### 2 ToString verification

#### The technique

If we print the array in the above sample, we can instead verify the whole thing with
```cpp
REQUIRE( "[Clare,Llewellyn,Simon,James,Emily]" == toString(names));
```

#### The problem
This works well, until you start to get large multi-line strings.

---

[Back to User Guide](/doc/README.md#top)
