<a id="top"></a>

# Testing Exceptions

**Contents**

<!-- vscode-markdown-toc -->
* [Testing exception messages](#Testingexceptionmessages)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->


## <a name='Testingexceptionmessages'></a>Testing exception messages

Testing exceptions with Approval Tests is very easy. Simply pass in a call to the function (usually wrapped in a lambda). Approval tests will execute the code, catch the exception, and verify the exception's message, i.e. `exception.what()`.

The exception thrown must inherit `std::exception`.

snippet: verify_exception_message_example

---

[Back to User Guide](README.md#top)
