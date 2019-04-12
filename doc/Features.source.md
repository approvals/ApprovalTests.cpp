<a id="top"></a>

# Features



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Using sub-directories for approved files](#using-sub-directories-for-approved-files)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Using sub-directories for approved files

If you have a lot of approval files, you might want to put them in a subdirectory, to prevent them cluttering up your source files. You can do this at a global or per-test level, by adding the line:

snippet: use_subdirectory_in_main

The return value will restore the original directory when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

This mechanism allows you to select a different sub-directory in individual tests.


---

[Back to User Guide](README.md#top)
