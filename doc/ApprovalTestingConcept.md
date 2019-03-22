<!--
This file was generate by MarkdownSnippets.
Source File: /doc/ApprovalTestingConcept.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>
# ApprovalTesting (the concept)

this is also referred to as snapshot testing, or golden master testing

## The Idea
Most tests have you explicitly state what is expected before you write the code,
ApprovalTesting, instead has you state the data you are interested in checking,
has you manually check it until you decide you are satisfied and then continues
to ensure it remains consistent for the future.

ApprovalTesting also harnesses the power of other tools to make
the results, and the differences in results, easier to understand and act on.



## The Path

### 1. Simple verification

#### The technique

Most of us are familiar with simple checks for numbers or strings.
```
REQUIRE( 1 == count);
REQUIRE( "Claire" == name);
```

#### The problem
But this can get complicated if you have a large list or object with many fields.
```
REQUIRE( "Claire" == names[0]);
REQUIRE( "Llewellyn" == names[1]);
REQUIRE( "Simon" == names[2]);
REQUIRE( "James" == names[3]);
REQUIRE( "Emily" == names[4]);
```

One solution for this is to start writing objects to string that are easier to verify.

### 2. ToString verification

#### The technique

If we print the array in the above sample, we can instead verify the whole thing with
```
REQUIRE( "[Claire,Llewellyn,Simon,James,Emily]" == toString(names));
```

#### The problem
This works well, until you start to get large multi-line strings.


---

[Back to User Guide](README.md#top)
