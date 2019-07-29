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

Currently, Approval Tests overrides any [`--reporter` command-line argument](https://github.com/onqtam/doctest/blob/master/doc/markdown/reporters.md) supplied.
This is needed for Approval Tests to function with doctest. The Approval Tests reporter works like doctest's `console` reporter. This means that it is not possible to run Approval Tests with the doctest test framework, and use reporters such as `xml`.

We currently do not have a better workaround.

---

[Back to User Guide](/doc/README.md#top)
