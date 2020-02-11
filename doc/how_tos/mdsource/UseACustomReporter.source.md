<a id="top"></a>

# How To Use A Custom Reporter

toc

This guide is for creating the ability to use a custom reporter that works on your machine.

For figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request, check out [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top).

Let's say that you really enjoy using Sublime Merge, and on your system it's located in `"/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge"`

If you were to run this the command line, the full command would look this this:

snippet: CustomReporterTests.Creating_Custom_Reporters.approved.txt

You can do this simply by creating a Reporter using:

snippet: use_custom_reporter

By default, this will run in the background. Most of the time this is what you want.

<!--
However, **COMING SOON!** you can force it to run in the foreground with:

```c++
auto reporter = CustomReporter::createForegroundReporter(path, arguments);
```
-->

On Windows, you can specify a search path for the installed location of a program with `{ProgramFiles}`.

snippet: use_custom_windows_reporter

See [Registering a default reporter](/doc/Reporters.md#registering-a-default-reporter) for wiring up this reporter as default, or you can dereference it and pass it in to individual `verify("text", *reporter)` method calls...

---

[Back to User Guide](/doc/README.md#top)
