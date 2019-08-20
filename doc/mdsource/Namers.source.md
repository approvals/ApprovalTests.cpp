<a id="top"></a>

# Namers

toc

## The Purpose of Namers

`Approvals::verify(text);`

could be written as:

`REQUIRE(text == (loadContentsFromFile("FileName.TestName.approved.txt"));`

Part of Approval Tests' "Convention over Configuration" is to remove this by automatically creating meaningful file names, and therefore it could be written as:

`REQUIRE(text == (loadContentsFromFile(namer.getApprovedFile()));`

"If you **always** have to do something, you should **never** have to do something."

Since all of your `REQUIRE`s would look like this, we can simplify it with the above `Approvals::verify(text);` - and this is enabled by the ApprovalNamers.

## The Parts of Namers

The conventional layout for files saved with `Approvals::verify()` and related functions is:

* `path_to_test_file/FileName.TestName.approved.txt`
* `path_to_test_file/FileName.TestName.received.txt`

The Approval Namer is responsible for creating these two names.

The interface for this is [`ApprovalNamer`](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/namers/ApprovalNamer.h).




## Registering a Custom Namer

If you ever want to create a custom namer, Approval Tests has a mechanism to change which namer it uses by default. Please note that you need to create a function that creates new namers.


snippet: register_default_namer

---

[Back to User Guide](/doc/README.md#top)
