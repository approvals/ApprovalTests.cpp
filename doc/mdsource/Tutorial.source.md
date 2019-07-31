<a id="top"></a>

# Tutorial

toc

The tutorial is written for someone with a decent understanding of C++, a passing understanding of traditional unit testing, and no experience with Approval Tests at all.

In this tutorial, we are going to use Windows, Catch2 and WinMerge. If you are using something else, it will make almost no difference to your experience.

By the end of this tutorial, you should be able to use Approval Tests in most basic cases.

To follow along at home, please [download the Starter Project](/doc/Setup.md#i-have-nothing).

## Hello Approval Tests

Let's open the Starter Project in your development environment, and open [Tutorial.cpp](https://github.com/approvals/ApprovalTests.cpp.StarterProject/blob/master/tests/Tutorial.cpp).

### Writing the Test 

Let's add our first test:

snippet: hello_approvals

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

Approval Tests keeps its expected result in an external file. When you run, it reads this file to do its verification.

If it matches, the test passes, and everything is finished.

However, if it does not match, another step is invoked, and a "[Reporter](/doc/Reporters.md#top)" (the Diff Tool)  is launched. This allows you to easily view and gain insight in to what happened and decide what you want to happen.

Please note that the first time you run an Approval Test, it will always fail and launch a reporter, as you have never said anything is OK.

### Approval Files

Approvals creates a lot of `.approved.txt` and `received.txt` files. The `received.txt` files are automatically deleted on a passing test, and should never be checked in to source control. We suggest adding `*.received.*` line to your `.gitignore` file.

The  `.approved.txt` files, on the other hand, need to be checked in to your source control.

Approval Tests follows the [Convention over Configuration](/doc/Glossary.md#convention-over-configuration) rule. The convention used for our files is as follows:

`FileName.TestName.approved.txt`

So in this case, it will be

`Tutorial.HelloApprovals.approved.txt`

It will be located in the same directory as your tests. (This is [configurable](doc/Configuration.md#using-sub-directories-for-approved-files)).

## Video

![Intro Graphic](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true)

---

[Back to User Guide](/doc/README.md#top)
