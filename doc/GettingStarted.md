# Catch 1 and 2

## New Project

``` cpp
#define APPROVALS_CATCH
#include "../ApprovalTests/Catch2Approvals.h"
```

## Existing Project

TODO

# Google Test

## Starter Project

TODO

## New Project

``` cpp
#define APPROVALS_GOOGLETEST
#include "../ApprovalTests/GoogleTestApprovals.h"
```

## Existing Project

``` cpp
#define APPROVALS_GOOGLETEST_EXISTING_MAIN
#include "../ApprovalTests/GoogleTestApprovals.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    initializeApprovalTestsForGoogleTests();
    return RUN_ALL_TESTS();
}
```
