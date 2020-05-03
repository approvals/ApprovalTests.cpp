<a id="top"></a>

# Using Approval Tests With doctest


toc


## Requirements

Approval Tests for doctest requires that a file called the following is found:

snippet: required_header_for_doctest

Approval Tests needs doctest version 2.3.4 or above.

## Getting Started With doctest

The [doctest](https://github.com/onqtam/doctest) test framework works well with Approval Tests.

include: include_ninja_warning_note

Doctest is similar to Catch, but claims to give faster compilation times.

### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: doctest_main

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for doctest](https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

snippet: doctest_existing_main

---

[Back to User Guide](/doc/README.md#top)
