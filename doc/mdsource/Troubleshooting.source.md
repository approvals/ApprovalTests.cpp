<a id="top"></a>

# Troubleshooting


toc


## Test gives "You have forgotten to configure your test framework..."

**Symptom**

Running tests gives the following output:

snippet: ForgottenToConfigure.HelpMessage.approved.txt 

**Things to check:**

See [Troubleshooting Misconfigured Main](/doc/TroubleshootingMisconfiguredMain.md#top).

## Test gives "There seems to be a problem with your build configuration"

**Symptom 1: Compilation Error**

Compiling tests in Ninja-generated builds gives a compilation failure, with this message:

snippet: compiler_error_for_misconfigured_build

**Symptom 2: Test Failure**

Running tests in Ninja-generated builds gives output such as the following:

snippet: ForgottenToConfigure.HelpMessageForIncorrectBuildConfig.approved.txt

**Things to check:**

See [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).

## My custom reporter works in development, but not CI

Check your test code - especially your main - for any uses of `Approvals::useAsFrontLoadedReporter()` that are specific to running on a Continuous Integration system.

If that's the case, and you do still want to use a custom reporter in an individual test, you can use `Approvals::useAsFrontLoadedReporter()` in the test, passing in your custom reporter, to take precedence over the CI-specific reporter in your main.

## Running Catch2 tests in CLion gives 'unexpected exception'

If there are problems with code that uses Approval Tests, or test failures, the library takes care to issue helpful information via the text in an exception (via `exception.what()`). This text is the displayed by the test framework.

However, some Catch2 users have reported not always seeing these messages, and instead seeing output like:

```
.../TestFileName.cpp:32: Failure:
unexpected exception
```

This turns out to be due to a bug in CLion's Catch2 plugin: [Catch2 unexpected exception instead of detailed message](https://youtrack.jetbrains.com/issue/CPP-11919).

There are various options to work around this:

* Try updating CLion or reviewing the linked ticket above, to see if the CLion problem has been fixed.
* Run the test executable in a console window, instead of in CLion, to see what the error is, and fix it.
* Use CLion's "Edit Configurations" to run the test program as a "CMake Application" instead of via the "Catch" test runner.

---

[Back to User Guide](/doc/README.md#top)
