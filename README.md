CppApprovals
============

[![Build Status](https://api.travis-ci.org/approvals/ApprovalTests.cpp.svg?branch=master)](https://travis-ci.org/approvals/ApprovalTests.cpp)

Native ApprovalTests for C++

Currently working in Mac/Linux with Catch2


## Getting Started

I Highly suggest you clone [The Approval.cpp Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)

## Main File

you need to include 2 lines for your main file to work.

``` cpp
#define APPROVALS_CATCH
#include "ApprovalTests.hpp"
```

For all other files, you only need
``` cpp
#include "ApprovalTests.hpp"
```
