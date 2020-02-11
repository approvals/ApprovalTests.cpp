<a id="top"></a>

# How To Use A Custom Reporter

toc

This guide is for creating the ability to use a custom reporter that works on your machine.

For figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request, check out 'How to Create and Submit a New Reporter to ApprovalTests.cpp'

Let's say that you really enjoy using Sublime Merge, and on your system it's located in `"/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge"`

If you were to run this the command line, the full command would look this this:

```bash
"/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge" \
    mergetool --no-wait test.received.txt test.approved.txt -o test.approved.txt
```

You can do this simply by creating a Reporter using:

```c++
auto path = "/Applications/Sublime Merge.app/Contents/SharedSupport/bin/smerge";
auto arguments = "mergetool --no-wait {Received} {Approved} -o {Approved}";
auto reporter = CustomReporter::create(path, arguments);
```

By default, this will run in the background. Most of the time this is what you want.

However, you can force it to run in the foreground with:

```c++
auto reporter = CustomReporter::createForegroundReporter(path, arguments);
```

On Windows, you can specify a search path for the installed location of a program with `{ProgramFiles}`.

TODO Note the inconsistent case of the values in `{}` - we used lower-case for `{Received}` and `{Approved}`.

```c++
auto path = "{ProgramFiles}Beyond Compare 4\\BCompare.exe";
auto arguments = "{Received} {Approved}"; // Do we want to make these values the default?
auto reporter = CustomReporter::create(path, arguments);
```

See TODO for wiring up this reporter as default, or pass it in to individual `verify()` method calls...

---

[Back to User Guide](/doc/README.md#top)