# Catch 1 and 2

## New Project

snippet: catch_2_main

## Existing Project

TODO

# Google Test

## Starter Project

TODO

## New Project

snippet: googletest_main

## Existing Project

``` cpp
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "ApprovalTests.hpp"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
```

## Cookbook

* [To String](ToString.md)
