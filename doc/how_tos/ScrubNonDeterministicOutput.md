<a id="top"></a>

# How to Scrub Non-Deterministic Output

<!-- toc -->
## Contents

  * [Scrubbers](#scrubbers)
  * [Lambda example](#lambda-example)
  * [Pre-made Scrubbers](#pre-made-scrubbers)
    * [Regular Expressions (regex)](#regular-expressions-regex)
      * [API for scrubbing with regex](#api-for-scrubbing-with-regex)
      * [Using a regex search term](#using-a-regex-search-term)
      * [Using a lambda for greater control of replacement text](#using-a-lambda-for-greater-control-of-replacement-text)
      * [See also](#see-also)
    * [GUID](#guid)<!-- endToc -->

## Scrubbers

This page assumes that you understand the concept of [Scrubbers](/doc/explanations/Scrubbers.md#top).

## Lambda example

<!-- snippet: scrubbing_via_lambda -->
<a id='snippet-scrubbing_via_lambda'></a>
```cpp
using namespace ApprovalTests;
Approvals::verify(
    "1 2 3 4 5 6",
    Options().withScrubber(
        [](const std::string& t) {return StringUtils::replaceAll(t, "3", "Fizz");}
    ));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/GuidScrubberTests.cpp#L79-L86' title='Snippet source file'>snippet source</a> | <a href='#snippet-scrubbing_via_lambda' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This would produce:

<!-- snippet: GuidScrubberTests.Scrubbing_via_Lambda.approved.txt -->
<a id='snippet-GuidScrubberTests.Scrubbing_via_Lambda.approved.txt'></a>
```txt
1 2 Fizz 4 5 6
```
<sup><a href='/tests/DocTest_Tests/scrubbers/approval_tests/GuidScrubberTests.Scrubbing_via_Lambda.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-GuidScrubberTests.Scrubbing_via_Lambda.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

(In the real world, scrubbers are generally used to remove text that is expected to differ between test runs... Here, we use a trivial example for ease of explanation.)

## Pre-made Scrubbers

### Regular Expressions (regex)

#### API for scrubbing with regex

Approval Tests provides lots of [convenience methods](https://approvaltestscpp.readthedocs.io/en/latest/api/scrubbers.html) to scrub text based on regular expressions.

#### Using a regex search term

For example, here is an example where random numbers are scrubbed:

<!-- snippet: simple_regex_scrubbing -->
<a id='snippet-simple_regex_scrubbing'></a>
```cpp
using namespace ApprovalTests;
std::stringstream os;
os << "Hello " << random(1000) << " World";
Approvals::verify(os.str(),
                  Options(Scrubbers::createRegexScrubber(R"(\d+)", "[number]")));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/ScrubberTests.cpp#L48-L54' title='Snippet source file'>snippet source</a> | <a href='#snippet-simple_regex_scrubbing' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This will produce:

<!-- snippet: ScrubberTests.createRegexScrubber_with_fixed_result.approved.txt -->
<a id='snippet-ScrubberTests.createRegexScrubber_with_fixed_result.approved.txt'></a>
```txt
Hello number World
```
<sup><a href='/tests/DocTest_Tests/scrubbers/approval_tests/ScrubberTests.createRegexScrubber_with_fixed_result.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-ScrubberTests.createRegexScrubber_with_fixed_result.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

**Note**: In the above example, the caller passes in a `std::string`, and for convenience of the calling code, Approval
Tests converts that to a `std::regex`. The calling code is responsible for making sure that the string contains a valid
regular expression.

#### Using a lambda for greater control of replacement text

There are many combinations of these parameters, that allow for customization at whatever level you
need, the most complex being:

<!-- snippet: complex_regex_scrubbing -->
<a id='snippet-complex_regex_scrubbing'></a>
```cpp
auto input = "1) Hello 1234 World";
auto scrubber = ApprovalTests::Scrubbers::createRegexScrubber(
    std::regex(R"(\d+)"), [](const auto& match) {
        auto match_text = match.str();
        auto match_integer = std::stoi(match_text);
        if (match_integer < 10)
        {
            return match_text;
        }
        else
        {
            return std::string("[number]");
        }
    });
```
<sup><a href='/tests/DocTest_Tests/scrubbers/ScrubberTests.cpp#L19-L34' title='Snippet source file'>snippet source</a> | <a href='#snippet-complex_regex_scrubbing' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

This will produce:

<!-- snippet: ScrubberTests.createRegexScrubber.approved.txt -->
<a id='snippet-ScrubberTests.createRegexScrubber.approved.txt'></a>
```txt
1) Hello [number] World
```
<sup><a href='/tests/DocTest_Tests/scrubbers/approval_tests/ScrubberTests.createRegexScrubber.approved.txt#L1-L1' title='Snippet source file'>snippet source</a> | <a href='#snippet-ScrubberTests.createRegexScrubber.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

#### See also

* [API Reference for Scrubbers](https://approvaltestscpp.readthedocs.io/en/latest/api/scrubbers.html)
* [Regex Tutorial](https://regexone.com/)
* [Regex Cheat Sheet](https://www.rexegg.com/regex-quickstart.html)
* [Regex Testing Tool](https://regex101.com)
* [C++ Regex Reference](https://en.cppreference.com/w/cpp/regex)

### GUID

You can scrub GUIDs by using a pointer to the function `Scrubbers::scrubGuid`.
 
For example the following code:

<!-- snippet: guid_scrubbing -->
<a id='snippet-guid_scrubbing'></a>
```cpp
using namespace ApprovalTests;
std::string jsonFromRestCall = R"(
    {
        child: {
            id: b34b4da8-090e-49d8-bd35-7e79f633a2ea
            parent1: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
            parent2: 05f77de3-3790-4d45-b045-def96c9cd371
        }
        person: {
            name: mom
            id: 2fd78d4a-ad49-447d-96a8-deda585a9aa5
        }
        person: {
            name: dad
            id: 05f77de3-3790-4d45-b045-def96c9cd371
        }
    }
    )";
Approvals::verify(jsonFromRestCall, Options().withScrubber(Scrubbers::scrubGuid));
```
<sup><a href='/tests/DocTest_Tests/scrubbers/GuidScrubberTests.cpp#L31-L51' title='Snippet source file'>snippet source</a> | <a href='#snippet-guid_scrubbing' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

will produce:

<!-- snippet: GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt -->
<a id='snippet-GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt'></a>
```txt
{
            child: {
                id: guid_1
                parent1: guid_2
                parent2: guid_3
            }
            person: {
                name: mom
                id: guid_2
            }
            person: {
                name: dad
                id: guid_3
            }
        }
```
<sup><a href='/tests/DocTest_Tests/scrubbers/approval_tests/GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt#L1-L17' title='Snippet source file'>snippet source</a> | <a href='#snippet-GuidScrubberTests.Input_with_multiple_GUIDs.approved.txt' title='Start of snippet'>anchor</a></sup>
<!-- endSnippet -->

Notice that when GUIDs are repeated within the same file, they are replaced with the same text.

---

[Back to User Guide](/doc/README.md#top)
