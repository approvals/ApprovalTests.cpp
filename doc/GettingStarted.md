<!--
This file was generate by MarkdownSnippets.
Source File: \doc\GettingStarted.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->

# Catch 1 and 2

## New Project

<!-- snippet: catch_2_main -->
```cpp
#define APPROVALS_CATCH
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_Catch2_Tests/main.cpp#L4-L7)</sup>
<!-- endsnippet -->

## Existing Project

TODO

# Google Test

## Starter Project

TODO

## New Project

<!-- snippet: googletest_main -->
```cpp
#define APPROVALS_GOOGLETEST
#include "ApprovalTests.hpp"
```
<sup>[snippet source](/ApprovalTests_GoogleTest_Tests/main.cpp#L2-L5)</sup>
<!-- endsnippet -->

## Existing Project

<!-- snippet: googletest_existing_main -->
```cpp
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
```
<sup>[snippet source](/examples/googletest_existing_main/main.cpp#L1-L11)</sup>
<!-- endsnippet -->

## Cookbook

* [To String](ToString.md)
