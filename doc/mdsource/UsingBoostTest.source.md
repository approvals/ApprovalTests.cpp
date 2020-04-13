<a id="top"></a>

# Using Approval Tests With Boost.Test


toc


## Getting Started With Boost.Test

The [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html) test framework works well with Approval Tests.

### Requirements

Approval Tests for Boost.Test requires that you specify the #include `<.../unit_test.hpp>`  
This allows ApprovalTests to work with all the different configurations of boost.  

Approval Tests needs Boost.Test version 1.60.0 or above.

### Adding Approvaltests to your Boost.Test

To enable any Boost.Test test files to use ApprovalTests, 
add the following lines of code to your [Test module's entry point](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/boost_test/adv_scenarios/entry_point_overview.html) 
after the boost headers:

snippet: boost_test_main

---

[Back to User Guide](/doc/README.md#top)
