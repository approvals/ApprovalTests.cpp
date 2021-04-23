<a id="top"></a>

# Contributing to ApprovalTests.cpp

<!-- toc -->
## Contents

  * [Contributing - pairing and pull requests](#contributing---pairing-and-pull-requests)
    * [Definition of Done](#definition-of-done)
  * [Code of Conduct](#code-of-conduct)
  * [Formatting Code](#formatting-code)
  * [Updating the simulated single-header](#updating-the-simulated-single-header)
  * [Coding Patterns](#coding-patterns)
  * [Documentation](#documentation)
  * [Releases](#releases)
  * [Running shell scripts in cygwin](#running-shell-scripts-in-cygwin)<!-- endToc -->

## Contributing - pairing and pull requests

The default way to add to most repositories is to fork and then create a pull-request.

This is **NOT** the default way to contribute to Approval Tests!

If you have something that you would like Approval Tests to have, including a bug you would like removed, we suggest you set up a pairing session (usually Skype or Facetime) with either [Llewellyn](mailto:llewellyn.falco@gmail.com) or [Clare](mailto:github@cfmacrae.fastmail.co.uk) or both.

A typical session lasts between 60 to 90 minutes. We do the work directly on master, on our own machines, with screen-sharing, and commit and push the results throughout the session. This results in quicker, higher-quality work. It gives us a better understanding of how people are using Approval Tests and the problems they encounter with it, and these sessions are also quite fun.

We use github's "co-author" feature, so everyone in the pairing session gets credit for the work. Virtually this entire project has been developed in this way, and is stronger for it.

Example co-author text, for use if not using the GitHub Desktop application:

```
Co-Authored-By: Llewellyn Falco <isidore@users.noreply.github.com>
```

We use [Arlo's Commit Notation](https://github.com/RefactoringCombos/ArlosCommitNotation) to prefix most commits, to indicate their level of risk.

### Definition of Done

*Note: Reminder for Clare and Llewellyn*

* [ ] Tests
* [ ] Documentation
    * [ ] Sample code
    * [ ] Copy+pastable template (if appropriate)
    * [ ] A link on [Features](https://github.com/approvals/ApprovalTests.cpp/blob/master/doc/Features.md#top)
    * [ ] A link on [build/relnotes_x.y.z.md](https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_x.y.z.md)
    * [ ] Links on other appropriate places
* [ ] Check the [Dashboard](https://github.com/claremacrae/dashboard#top) (after pushing)
* [ ] Retrospective (as an experiment) on what we learned from the work

## Code of Conduct

Please note that this project is released with a [Contributor Code of Conduct](/CODE_OF_CONDUCT.md#top). By participating in this project you agree to abide by its terms.

## Formatting Code

If possible, please configure your editor to use this repository's [.clang-format](https://github.com/approvals/ApprovalTests.cpp/blob/master/.clang-format) file.

Instructions for this are available:

* CLion:
    * Settings/Preferences | Editor | Code Style | Turn on "Enable ClangFormat with clangd server" checkbox.
    * More information: [ClangFormat as Alternative Formatter](https://www.jetbrains.com/help/clion/clangformat-as-alternative-formatter.html)

There is a script to apply clang-format to the whole project: [scripts/reformat_code.sh](https://github.com/approvals/ApprovalTests.cpp/blob/master/scripts/reformat_code.sh).

We have a CI job called `clang-format` that checks for code not correctly formatted: [.github/workflows/github_actions_build.yml](https://github.com/approvals/ApprovalTests.cpp/blob/master/.github/workflows/github_actions_build.yml).

## Updating the simulated single-header

After adding new header files to the library, we need to update [ApprovalTests/ApprovalTests.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/ApprovalTests.hpp).

This is done by running [scripts/create_simulated_single_header.sh](https://github.com/approvals/ApprovalTests.cpp/blob/master/scripts/create_simulated_single_header.sh):

```bash
cd ApprovalTests.cpp
./scripts/create_simulated_single_header.sh
```

## Coding Patterns

See [Static variables for header-only releases](/doc/CodingPatterns.md#static-variables-for-header-only-releases).

## Documentation

We welcome improvements to the documentation! The page [Maintaining the Docs](doc/MaintainingDocumentation.md#top) describes how we manage the documentation files. 

## Releases

* Everything for releases is in [the build directory](/build/)
* There's more information in [How to Release](/build/HowToRelease.md#top)

## Running shell scripts in cygwin

To run `.sh` in cygwin on Windows, add these lines to `~/.bash_profile`, and then re-start cygwin:

```bash
export SHELLOPTS
set -o igncr
```

[Credit](https://ptolemy.berkeley.edu/projects/chess/softdevel/faq/5.html)

---

[Back to User Guide](/doc/README.md#top)
