<a id="top"></a>

# Testing Exceptions

toc



## Testing exception messages

Testing exceptions with Approval Tests is very easy. Simply pass in a call to the function (usually wrapped in a lambda). Approval tests will execute the code, catch the exception, and verify the exception's message, i.e. `exception.what()`.

The exception thrown must inherit `std::exception`.

snippet: verify_exception_message_example

## Handling multiple exceptions in one test

See [ExceptionCollector](/doc/Utilities.md#exceptioncollector).

---

[Back to User Guide](/doc/README.md#top)
