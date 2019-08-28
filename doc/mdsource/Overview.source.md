<a id="top"></a>

# Overview of Approval Tests

toc

## Summary

Approval Tests are an alternative way to write asserts in your test code.

As the following examples demonstrate, they give significantly simpler tests of complex objects.

## Traditional Asserts

Traditional tests spend equal time focusing on creating the inputs and verifying the outputs. 

When the objects being tested are non-trivial, either the tests become quite verbose (as shown in this example), or it's tempting to only test a small part of the behaviour.

snippet: sandwich_example_with_requires

## Approval Tests

Approval Tests simplify verification of the outputs. They do this by writing the outputs to a file, which once saved, becomes your spec.

You still supply the inputs, but Approval Tests gives you powerful ways of viewing complex outputs, meaning you can move on to the next feature or next test more quickly.

snippet: sandwich_example_with_approvals

This generates the approval file - which generated **for** you, but [approved **by** you](/doc/ApprovingResults.md#top).

snippet: OverviewExamples.SandwichExampleWithApprovals.approved.txt

---

[Back to User Guide](/doc/README.md#top)
