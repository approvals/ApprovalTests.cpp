<a id="top"></a>

# Reporter



<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [Registering a default reporter](#registering-a-default-reporter)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Registering a default reporter

At present, the default Reporter is the DiffReporter. Whenever you call Approvals, you have the chance to pass in your own Reporter. However, if you would like to change what the default reporter is when you don't pass in a specific Reporter, you can do this at a global or per-test level, by adding the line:

snippet: use_as_default_reporter_in_main

The return value will restore the original reporter when the object destructs. Because of this, if you do not store the result in a variable, it will immediately undo itself by the end of the line.

---

[Back to User Guide](README.md#top)
