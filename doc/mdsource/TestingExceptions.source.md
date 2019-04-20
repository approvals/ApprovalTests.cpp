<a id="top"></a>

# Testing Exceptions



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Testing exception messages](#testing-exception-messages)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


## Testing exception messages

Testing exceptions with Approval Tests is very easy. Simply pass in a call to the function (usually wrapped in a lambda). Approval tests will execute the code, catch the exception, and verify the exception's message, i.e. `exception.what()`.

The exception thrown must inherit `std::exception`.

snippet: verify_exception_message_example

---

[Back to User Guide](README.md#top)
