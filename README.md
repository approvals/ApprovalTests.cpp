CppApprovals
============

[![Build Status](https://api.travis-ci.org/approvals/ApprovalTests.cpp.svg?branch=master)](https://travis-ci.org/approvals/ApprovalTests.cpp)

[![Build status](https://ci.appveyor.com/api/projects/status/lf3i76ije89oihi5?svg=true)](https://ci.appveyor.com/project/isidore/approvaltests-cpp)

Native ApprovalTests for C++

![Intro Graphic](doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)

Currently working in Mac/Linux/Windows with
* [Catch1](https://github.com/catchorg/Catch2/tree/Catch1.x)  
* [Catch2](https://github.com/catchorg/Catch2)   
* [Okra](https://github.com/JayBazuzi/Okra) & C++ 11  
* [GoogleTest](https://github.com/google/googletest)



## Getting Started

[More details here](doc/GettingStarter.md)

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

## Examples
ApprovalTests uses ApprovalTests to test ApprovalTests (it's turtles all the way down)  
[Checkout our own tests](https://github.com/approvals/ApprovalTests.cpp/tree/master/ApprovalTests_Catch2_Tests) to see how we do it:

### ToString (ostream insertion)
Often, you will need to create functions to allow objects to print their state. This is commonly done with on ostream << operator.
You can find an example here:
[Printable Objects](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/ToStringExample.cpp)

### Suggested Examples:
[ApprovalTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/ApprovalsTests.cpp)
[VectorTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/VectorTests.cpp)
[CombinationTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests_Catch2_Tests/CombinationTests.cpp)  
