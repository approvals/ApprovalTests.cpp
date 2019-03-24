<!--
This file was generate by MarkdownSnippets.
Source File: /doc/ApprovalTestingConcept.source.md
To change this file edit the source file and then re-run the generation using either the dotnet global tool (https://github.com/SimonCropp/MarkdownSnippets#githubmarkdownsnippets) or using the api (https://github.com/SimonCropp/MarkdownSnippets#running-as-a-unit-test).
-->
<a id="top"></a>

# ApprovalTesting (the concept)

**Contents**

<!-- vscode-markdown-toc -->
* [The Idea](#TheIdea)
* [The Path](#ThePath)
	* [1 Simple verification](#Simpleverification)
		* [The technique](#Thetechnique)
		* [The problem](#Theproblem)
	* [2 ToString verification](#ToStringverification)
		* [The technique](#Thetechnique-1)
		* [The problem](#Theproblem-1)

<!-- vscode-markdown-toc-config
	numbering=false
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc -->

this is also referred to as snapshot testing, or golden master testing

## <a name='TheIdea'></a>The Idea
Most tests have you explicitly state what is expected before you write the code,
ApprovalTesting, instead has you state the data you are interested in checking,
has you manually check it until you decide you are satisfied and then continues
to ensure it remains consistent for the future.

ApprovalTesting also harnesses the power of other tools to make
the results, and the differences in results, easier to understand and act on.



## <a name='ThePath'></a>The Path

### <a name='Simpleverification'></a>1 Simple verification

#### <a name='Thetechnique'></a>The technique

Most of us are familiar with simple checks for numbers or strings.
```
REQUIRE( 1 == count);
REQUIRE( "Clare" == name);
```

#### <a name='Theproblem'></a>The problem
But this can get complicated if you have a large list or object with many fields.
```
REQUIRE( "Clare" == names[0]);
REQUIRE( "Llewellyn" == names[1]);
REQUIRE( "Simon" == names[2]);
REQUIRE( "James" == names[3]);
REQUIRE( "Emily" == names[4]);
```

One solution for this is to start writing objects to string that are easier to verify.

### <a name='ToStringverification'></a>2 ToString verification

#### <a name='Thetechnique-1'></a>The technique

If we print the array in the above sample, we can instead verify the whole thing with
```
REQUIRE( "[Clare,Llewellyn,Simon,James,Emily]" == toString(names));
```

#### <a name='Theproblem-1'></a>The problem
This works well, until you start to get large multi-line strings.


---

[Back to User Guide](README.md#top)
