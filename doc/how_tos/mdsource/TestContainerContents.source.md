<a id="top"></a>

# How to Test the Contents of a Container

toc

## When to test a container

You have called a method that returns a collection of objects, and you want a nicer read-out than the standard verify() will give you.

## Steps

1. Copy this starter text.

snippet: VerifyAllStartingPointContainer

2. Replace the `objectsToVerify` container with your collection of objects.
3. Change the TITLE to something meaningful
4. Run it, and approve the output.

## More Examples

For some examples, see [VectorTests.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/VectorTests.cpp).

## Further Advice

For advice on effective formatting, see [To String](/doc/ToString.md#top). As you write out larger volumes of data in your approval files, experience has shown that the choice of layout of text in approval files can make a big difference to maintainability of tests, when failures occur.

---

[Back to User Guide](/doc/README.md#top)
