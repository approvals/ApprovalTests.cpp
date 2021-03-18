<a id="top"></a>

# <img src="doc/images/icon.png" height="30px"> Approval Tests for C++

[![Build status](https://ci.appveyor.com/api/projects/status/lf3i76ije89oihi5?svg=true)](https://ci.appveyor.com/project/isidore/approvaltests-cpp)
[![Actions Status](https://github.com/approvals/ApprovalTests.cpp/workflows/build/badge.svg?branch=master)](https://github.com/approvals/ApprovalTests.cpp/actions?query=branch%3Amaster+workflow%3Abuild)
[![Python tests](https://github.com/approvals/ApprovalTests.cpp/workflows/python-tests/badge.svg?branch=master)](https://github.com/approvals/ApprovalTests.cpp/actions?query=branch%3Amaster+workflow%3Apython-tests)  
[![Documentation Status](https://readthedocs.org/projects/approvaltestscpp/badge/?version=latest)](https://approvaltestscpp.readthedocs.io/en/latest/?badge=latest)
[![ConanCenter package](https://repology.org/badge/version-for-repo/conancenter/approvaltests.cpp.svg)](https://conan.io/center/approvaltests.cpp)  
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Contributor Covenant](https://img.shields.io/badge/Contributor%20Covenant-v1.4%20adopted-ff69b4.svg)](/CODE_OF_CONDUCT.md#top)

:arrow_down: <a href="https://github.com/approvals/ApprovalTests.cpp/releases/download/v.10.8.0/ApprovalTests.v.10.8.0.hpp">
Download the latest version (v.10.8.0) of the **single header file** here.</a>

:book: [**Read the Docs**](https://approvaltestscpp.readthedocs.io/en/latest/)

<!-- toc -->
## Contents

  * [What are Approval Tests?](#what-are-approval-tests)
  * [Requirements](#requirements)
  * [Getting Started](#getting-started)
  * [ToString (ostream insertion)](#tostring-ostream-insertion)
  * [What's new?](#whats-new)
  * [Feedback](#feedback)<!-- endToc -->

## What are Approval Tests?

Also known as **Golden Master Tests** or **Snapshot Testing**, Approval Tests are an alternative to asserts. If you are unfamiliar with them, we have an [overview](/doc/Overview.md#top) and a [tutorial](/doc/Tutorial.md#top).

They are great for testing objects with lots of fields, or lists of objects.

## Requirements

* C++11 (or above) compiler
* Mac/Linux/Windows
* One of:  [GoogleTest](https://github.com/google/googletest), [Catch2](https://github.com/catchorg/Catch2), [CppUTest](http://cpputest.github.io/), [doctest](https://github.com/onqtam/doctest), [Boost.Test](https://www.boost.org/doc/libs/1_72_0/libs/test/doc/html/index.html), [\[Boost\].UT](https://github.com/boost-experimental/ut)

## Getting Started

* Download [The Approval.cpp Starter Project](https://github.com/approvals/ApprovalTests.Cpp.StarterProject)
* Read the [Getting Started](/doc/GettingStarted.md#top) page
* [Set up your main file.](/doc/GettingStarted.md#main-file)
* Read the [**User Guide on Read the Docs**](https://approvaltestscpp.readthedocs.io/en/latest/) or
[**on GitHub**](/doc/README.md#top).
* Watch the [Videos](/doc/Videos.md#top)

## ToString (ostream insertion)
Often, you will need to create functions to allow objects to print their state. This is commonly done with an ostream `<< operator`.
You can find examples here: [To String](/doc/ToString.md#top)

## What's new?

Check out the [Features](/doc/Features.md#top) page or [upcoming release notes](https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_x.y.z.md) to see what we've been working on lately, or browse the [past release notes](https://github.com/approvals/ApprovalTests.cpp/releases).

## Feedback

If you have any comment or suggestion on this documentation, please email Llewellyn or Clare via the details in the [Contributing page](/doc/Contributing.md#top).
