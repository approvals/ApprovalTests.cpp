<a id="top"></a>

# Test Relative Links

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [This page is temporary!](#this-page-is-temporary)
- [Relative links to .md files](#relative-links-to-md-files)
- [Relative links to images files](#relative-links-to-images-files)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## This page is temporary!

This page is for testing relative links in `mdsource/.source.md` and corresponding `.md` files, to see how they behave.

Scenarios to test:

* CLion editor
* Browsing on Github
* Viewing in [Working Copy iOS github client](https://workingcopyapp.com/)

Pages to test:

* [doc/TestRelativeLinks.md](https://github.com/approvals/ApprovalTests.cpp/blob/mdsnippets_source_dir/doc/TestRelativeLinks.md)
* [doc/mdsource/TestRelativeLinks.source.md](https://github.com/approvals/ApprovalTests.cpp/blob/mdsnippets_source_dir/doc/mdsource/TestRelativeLinks.source.md)

## Relative links to .md files

| Link          | CLion             | Github UI             | Working Copy          |
| ------------- | ----------------- | --------------------- | --------------------- |
| [README.md#top](README.md#top)            | Link unresponsive         | | |
| [/doc/README.md#top](/doc/README.md#top)  | Opens link on github.com  | | |

## Relative links to images files

| Link          | CLion             | Github UI             | Working Copy          |
| ------------- | ----------------- | --------------------- | --------------------- |
| ![images/ApprovalTests.cpp.IntroGraphic.gif?raw=true](images/ApprovalTests.cpp.IntroGraphic.gif?raw=true) | Shows as broken image | |
| ![/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true](/doc/images/ApprovalTests.cpp.IntroGraphic.gif?raw=true) | Shows as broken image | | 

---

[Back to User Guide](README.md#top)
