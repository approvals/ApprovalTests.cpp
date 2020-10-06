<a id="top"></a>

# Tutorial

<!-- toc -->
## Contents

  * [Hello Approval Tests](#hello-approval-tests)
    * [Writing the Test](#writing-the-test)
    * [Approving the Test](#approving-the-test)
    * [What just happened?](#what-just-happened)
    * [Approval Files](#approval-files)
  * [The ApprovalTests namespace](#the-approvaltests-namespace)
  * [Approving Objects](#approving-objects)
  * [Dealing with test failures](#dealing-with-test-failures)
  * [Demo](#demo)<!-- endToc -->

The tutorial is written for someone with a decent understanding of C++, a passing understanding of traditional unit testing and of diff tools, and no experience with Approval Tests at all.

In this tutorial, we are going to use Windows, Catch2 and WinMerge. If you are using something else, it will make almost no difference to your experience.

By the end of this tutorial, you should be able to use Approval Tests in most basic cases.

To follow along at home, please [download the Starter Project](/doc/Setup.md#i-have-nothing).

## Hello Approval Tests

Let's open the Starter Project in your development environment, and open [Tutorial.cpp](https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/Tutorial.cpp).

### Writing the Test 

Let's add our first test:

<!-- snippet: hello_approvals -->
<a id='snippet-hello_approvals'></a>
```cpp
TEST_CASE("HelloApprovals")
{
    ApprovalTests::Approvals::verify("Hello Approvals");
}
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L16-L21' title='File snippet `hello_approvals` was extracted from'>snippet source</a> | <a href='#snippet-hello_approvals' title='Navigate to start of snippet `hello_approvals`'>anchor</a></sup>
<!-- endSnippet -->

### Approving the Test

When we run the test, WinMerge will open as such:

![New Failure](/doc/images/tutorial/01_new_failure.png?raw=true)

On the left hand side, we will see the actual received result, `Hello Approvals`. It is what we want, so we are going to approve it. To do that, click the "All Right" button (or copy and paste the text to the other side)
 
![Approving](/doc/images/tutorial/02_approving.png?raw=true)

Afterwards, the two sides should be identical.

![Approved](/doc/images/tutorial/03_approved.png?raw=true)

Now save the file and close the Diff Tool.

Now, when you re-run the tests, two things should happen:

1. The test should pass
2. The Diff Tool should **NOT** open.

### What just happened?

Approval Tests keeps its expected result in an external file. When you run the test, it reads this file to do its verification.

If it matches, the test passes, and everything is finished.

However, if it does not match, another step is invoked, and a "[Reporter](/doc/Reporters.md#top)" (the Diff Tool)  is launched. This allows you to easily view and gain insight in to what happened and decide what you want to happen.

Please note that the first time you run an Approval Test, it will always fail and launch a reporter, as you have never said anything is OK.

### Approval Files

Approvals creates a lot of `.approved.txt` and `.received.txt` files. The `.received.txt` files are automatically deleted on a passing test, and should never be checked in to source control. We suggest adding `*.received.*` line to your `.gitignore` file.

The  `.approved.txt` files, on the other hand, need to be checked in to your source control.

Approval Tests follows the [Convention over Configuration](/doc/Glossary.md#convention-over-configuration) rule. The convention used for our files is as follows:

`FileName.TestName.approved.txt`

So in this case, it will be:

`Tutorial.HelloApprovals.approved.txt`

It will be located in the same directory as your tests. (This is [configurable](/doc/Configuration.md#using-sub-directories-for-approved-files)).


## The ApprovalTests namespace

In all other code examples in this site, have already included the code:

<!-- snippet: using_namespace_approvaltests -->
<a id='snippet-using_namespace_approvaltests'></a>
```cpp
using namespace ApprovalTests;
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L8-L10' title='File snippet `using_namespace_approvaltests` was extracted from'>snippet source</a> | <a href='#snippet-using_namespace_approvaltests' title='Navigate to start of snippet `using_namespace_approvaltests`'>anchor</a></sup>
<!-- endSnippet -->

... So that code samples are simpler and easier to read. This is a recommended practice in your tests.

## Approving Objects

The above example is a bit simplistic. Normally, you will want to test actual objects from your code base. To explore this, let's create an object called `LibraryBook`:

<!-- snippet: library_book -->
<a id='snippet-library_book'></a>
```cpp
class LibraryBook
{
public:
    LibraryBook(std::string title_,
                std::string author_,
                int available_copies_,
                std::string language_,
                int pages_,
                std::string isbn_)
        : title(title_)
        , author(author_)
        , available_copies(available_copies_)
        , language(language_)
        , pages(pages_)
        , isbn(isbn_)
    {
    }
    // Data public for simplicity of test demo case.
    // In production code, we would have accessors instead.
    std::string title;
    std::string author;
    int available_copies;
    std::string language;
    int pages;
    std::string isbn;
};
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L23-L50' title='File snippet `library_book` was extracted from'>snippet source</a> | <a href='#snippet-library_book' title='Navigate to start of snippet `library_book`'>anchor</a></sup>
<!-- endSnippet -->

What we would like to be able to write is:

<!-- snippet: non_printable_object -->
<a id='snippet-non_printable_object'></a>
```cpp
LibraryBook harry_potter(
    "Harry Potter and the Goblet of Fire", "J.K. Rowling",
    30, "English", 752, "978-0439139595");

Approvals::verify(harry_potter); // This does not compile
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L56-L62' title='File snippet `non_printable_object` was extracted from'>snippet source</a> | <a href='#snippet-non_printable_object' title='Navigate to start of snippet `non_printable_object`'>anchor</a></sup>
<!-- endSnippet -->

The problem is that this will not compile, because at present there is no way to turn the LibraryBook in to a string representation.

So we are going to add a lambda to handle the printing.

Let's start by just printing the title:

<!-- snippet: printable_object_simple -->
<a id='snippet-printable_object_simple'></a>
```cpp
Approvals::verify(harry_potter, [](const LibraryBook& b, std::ostream& os) {
    os << "title: " << b.title;
});
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L75-L79' title='File snippet `printable_object_simple` was extracted from'>snippet source</a> | <a href='#snippet-printable_object_simple' title='Navigate to start of snippet `printable_object_simple`'>anchor</a></sup>
<!-- endSnippet -->

There's a lot going on here, so let's break it down:

1. Lambda: `[](const LibraryBook& b, std::ostream& os){}`. This is the call-back function to convert your object to a string. Note that you can also write this as `[](auto b, auto& os){}`
1. toString: `os << "title: " << b.title;` - this is the bit of code that actually turns our object in to a string.

This works, but of course, there is a lot more that we want to look at than the title. So let's expand the `toString`:

<!-- snippet: printable_object -->
<a id='snippet-printable_object'></a>
```cpp
Approvals::verify(harry_potter, [](const LibraryBook& b, std::ostream& os) {
    os << "title: " << b.title << "\n"
       << "author: " << b.author << "\n"
       << "available_copies: " << b.available_copies << "\n"
       << "language: " << b.language << "\n"
       << "pages: " << b.pages << "\n"
       << "isbn: " << b.isbn << "\n";
});
```
<sup><a href='/tests/DocTest_Tests/docs/Tutorial.cpp#L91-L100' title='File snippet `printable_object` was extracted from'>snippet source</a> | <a href='#snippet-printable_object' title='Navigate to start of snippet `printable_object`'>anchor</a></sup>
<!-- endSnippet -->

When you run and approve this, you will end up with the approval file:

<!-- snippet: Tutorial.WritableBooks2.approved.txt -->
<a id='snippet-Tutorial.WritableBooks2.approved.txt'></a>
```txt
title: Harry Potter and the Goblet of Fire
author: J.K. Rowling
available_copies: 30
language: English
pages: 752
isbn: 978-0439139595

```
<sup><a href='/tests/DocTest_Tests/docs/approval_tests/Tutorial.WritableBooks2.approved.txt#L1-L7' title='File snippet `Tutorial.WritableBooks2.approved.txt` was extracted from'>snippet source</a> | <a href='#snippet-Tutorial.WritableBooks2.approved.txt' title='Navigate to start of snippet `Tutorial.WritableBooks2.approved.txt`'>anchor</a></sup>
<!-- endSnippet -->

If you would like to know how to do this more robustly, check out [To String](/doc/ToString.md#top).

## Dealing with test failures

Every change in behaviour is not necessarily a failure, but every change in behaviour will fail the test.

There are three parts to dealing with failure.

1. Identify what changed
2. Either:
  * Fix the code, if the change was not intentional
  * Re-approve the test, if you want the new behaviour

If you are in a refactoring mode, changes in Approval Tests output files are usually unintended, and a sign that you might have made a mistake.

If you are adding a new feature, changes in Approval Tests output files are often intended, and a sign that you should review and maybe accept the modified output.

<!-- todo: custom asserts, pull out a verifyLibraryBook(book) method -->

## Demo

Here's a little video of the whole process.

![Intro Graphic](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)

---

[Back to User Guide](/doc/README.md#top)
