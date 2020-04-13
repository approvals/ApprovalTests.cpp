<a id="top"></a>

# Using Approval Tests With Boost.Test


toc


## Getting Started With Boost.Test

The [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html) test framework works well with Approval Tests.

### Requirements

Approval Tests for Boost.Test requires that you specify the #include `<.../unit_test.hpp>`  
This allows ApprovalTests to work with all the different configurations of boost.  

Approval Tests needs Boost.Test version 1.60.0 or above.

### New Project

Create a file `main.cpp` and add just the following two lines:

snippet: boost_test_main

<!-- todo: document use of sections -->

### Existing Project - with your main()

If you have [supplied your own `main()` for Boost.Test](hhttps://github.com/onqtam/Boost.Test/blob/master/doc/markdown/main.md#top), you will need to teach it how to supply test names to Approval Tests.

You should make the following additions to your own source file that contains `main()`.  

snippet: Boost.Test_existing_main

---

[Back to User Guide](/doc/README.md#top)
