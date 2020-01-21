<a id="top"></a>
# How To Release

## Update ApprovalTests.cpp

Preparation:

TODO Eliminate most of this...

- [ ] Determine the type of semantic - major, minor or patch 

Creating the Build

- Run one of:
  - majorRelease.py
  - minorRelease.py
  - patchRelease.py

Publishing

- [ ] Finish off the upload to github, by uploading the new .hpp, pasting in the release notes, and hitting "Publish release"
- [ ] Finish off the release Tweet
- [ ] Close any [Issues](https://github.com/approvals/ApprovalTests.cpp/issues) that were resolved in this release

Prepare for next release

- [ ] Change version number to current version number, and new version number to `$UNSET_VERSION`
- [ ] Make sure the release notes named with the new version exist
- [ ] `cp relnotes_template.md relnotes_X.X.X.md`
