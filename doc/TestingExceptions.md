<a id="top"></a>

# Testing Exceptions

<!-- toc -->
## Contents

  * [Testing exception messages](#testing-exception-messages)
  * [Handling multiple exceptions in one test](#handling-multiple-exceptions-in-one-test)<!-- endToc -->

## Testing exception messages

Testing exceptions with Approval Tests is very easy. Simply pass in a call to the function (usually wrapped in a lambda). Approval tests will execute the code, catch the exception, and verify the exception's message, i.e. `exception.what()`.

The exception thrown must inherit `std::exception`.

<!-- snippet: verify_exception_message_example -->
<a id='snippet-verify_exception_message_example'></a>
```cpp
ApprovalTests::Approvals::verifyExceptionMessage([]() { /* your code goes here */ });
```
<sup><a href='/tests/DocTest_Tests/ApprovalsExamples.cpp#L6-L8' title='Snippet source file'>snippet source</a> | <a href='#snippet-verify_exception_message_example' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

## Handling multiple exceptions in one test

See [ExceptionCollector](/doc/Utilities.md#exceptioncollector).

---

[Back to User Guide](/doc/README.md#top)
