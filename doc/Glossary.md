<a id="top"></a>

# Glossary

<!-- toc -->
## Contents

  * [Approving Results](#approving-results)
  * [Approved File](#approved-file)
  * [Chain of responsibility (pattern)](#chain-of-responsibility-pattern)
  * [Code Coverage](#code-coverage)
  * [Combination Testing](#combination-testing)
  * [Comparator](#comparator)
  * [Continuous Integration](#continuous-integration)
  * [Convention over Configuration](#convention-over-configuration)
  * [Custom Asserts](#custom-asserts)
  * [Diff Tool](#diff-tool)
  * [Disposable Objects](#disposable-objects)
  * [Edge Case](#edge-case)
  * [Fake It Till You Make It](#fake-it-till-you-make-it)
  * [Happy Path](#happy-path)
  * [Kata](#kata)
  * [Koans](#koans)
  * [Mutation Testing](#mutation-testing)
  * [Namer](#namer)
  * [Principle of Least Surprise](#principle-of-least-surprise)
  * [RAII (Resource acquisition is initialization)](#raii-resource-acquisition-is-initialization)
  * [Received File](#received-file)
  * [Reporter](#reporter)
  * [Scrubber](#scrubber)
  * [Stringification](#stringification)
  * [System Under Test](#system-under-test)
  * [Test Framework](#test-framework)
  * [test && commit || revert (TCR)](#test--commit--revert-tcr)
  * [Writer](#writer)
  * [Yak Shaving](#yak-shaving)
  * [Sayings](#sayings)<!-- endToc -->

## Approving Results

## Approved File

## Chain of responsibility (pattern)

## Code Coverage

## Combination Testing

Sometimes referred to as Combinatorial testing.

See [Testing Combinations](/doc/TestingCombinations.md#top).

## Comparator

See [Custom Comparators](/doc/CustomComparators.md#top).

## Continuous Integration

## Convention over Configuration  

[Wikipedia Entry](https://en.wikipedia.org/wiki/Convention_over_configuration)

Instead of asking the user to specify everything, we make assumptions based on common patterns, so code usually just works "out of the box". This tends to dramatically reduce the amount of clutter, makes things easier, and reduces the amount of surprises.

## Custom Asserts

## Diff Tool

## Disposable Objects

Objects that implement the [RAII](#raii-resource-acquisition-is-initialization) pattern.

See [Disposable Objects](/doc/DisposableObjects.md#top).

## Edge Case

## Fake It Till You Make It

[A development technique for building in small steps](https://stackoverflow.com/a/4169657/1303587)

## Happy Path

## Kata

## Koans

## Mutation Testing

## Namer

## Principle of Least Surprise

## RAII (Resource acquisition is initialization)

This is a pattern where your object constructor opens a resource, such as memory, and your object destructor closes the resource.

This is also known as "Scope based resource management".

[Wikipedia Entry](https://en.cppreference.com/w/cpp/language/raii)

## Received File

## Reporter

See [Reporters](/doc/Reporters.md#top).

See [Using sub-directories for approved files](/doc/Configuration.md#using-sub-directories-for-approved-files)

See [Features](/doc/Features.md#top) - whose sections need to be moved around

## Scrubber

See [Scrubbers](/doc/explanations/Scrubbers.md#top).

## Stringification

See [String conversions](/doc/ToString.md#top).

## System Under Test

The area of the production code that you are testing. See [System Under Test](https://en.wikipedia.org/wiki/System_under_test).

## Test Framework

## test && commit || revert (TCR)

## Writer

## Yak Shaving

---

## Sayings

* The tests test the code, and the code tests the tests
* Test until bored

---

[Back to User Guide](/doc/README.md#top)
