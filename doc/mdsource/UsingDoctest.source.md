<a id="top"></a>

# Using Approval Tests With doctest


toc



## Getting Started With doctest

The [doctest](https://github.com/onqtam/doctest) test framework works fairly well with Approval Tests.

Doctest is similar to Catch, but claims to give faster compilation times.

### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: doctest_main

## Limitations

### doctest --reporter argument ignored

Currently, Approval Tests overrides any [`--reporter` command-line argument](https://github.com/onqtam/doctest/blob/master/doc/markdown/reporters.md) supplied.
This is needed for Approval Tests to function with doctest. The Approval Tests reporter works like doctest's `console` reporter. This means that it is not possible to run Approval Tests with the doctest test framework, and use reporters such as `xml`.

We currently do not have a better workaround.

### Visual Studio compilation failure workaround

If you provide your own copy of the doctest header, and find this compiler error in Visual Studio, for a call to `std::max()`:

```
C:\projects\approvaltests-cpp\lib\doctest.2.3.3.hpp(3435,48): 
error C2589:  '(': illegal token on right side of '::' 
[...approvaltests-cpp\ApprovalTests_DocTest_Tests\ApprovalTests_DocTest_Tests.vcxproj]
C:\projects\approvaltests-cpp\lib\doctest.2.3.3.hpp(3435,48): 
error C2062:  type 'unknown-type' unexpected 
[...\approvaltests-cpp\ApprovalTests_DocTest_Tests\ApprovalTests_DocTest_Tests.vcxproj]
```

... you may need to apply [this fix to your doctest header](https://github.com/approvals/ApprovalTests.cpp/commit/d914f3233a5c354b54b660790ee7f6e8f0f1fd7c).

For the current status of this, see [doctest/pull/258](https://github.com/onqtam/doctest/pull/258).

---

[Back to User Guide](/doc/README.md#top)
