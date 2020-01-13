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

---

[Back to User Guide](/doc/README.md#top)
