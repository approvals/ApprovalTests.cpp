<a id="top"></a>
# How To Release

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Contents**

- [How To Release](#how-to-release)
  - [Update ApprovalTests.cpp](#update-approvaltestscpp)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Update ApprovalTests.cpp

Preparation:

* Check that the [builds are passing](https://github.com/approvals/ApprovalTests.cpp/commits/master)
* Write summary of changes since last release, based on changes since [the last release](https://github.com/approvals/ApprovalTests.cpp/releases)
* Determine the semantic version number
* Update the version number in [build_hpp.sh](build_hpp.sh)

Creating the build

* Run `build_hpp.sh` - this updates [the starter project](https://github.com/approvals/ApprovalTests.cpp.StarterProject), tests that it builds, and if so, **commits and pushes it**

Publishing

* Change version number to current version number, and new version number to v.X.X.X
* Commit and push `ApprovalTests.cpp`
* Finish off the upload to github, by uploading the new .hpp, pasting in the release notes, and hitting "Publish release"
* Finish off the release Tweet
* Optionally, change the version numbers in `build_hpp.sh` to reflect the next version
