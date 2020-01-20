<a id="top"></a>
# How To Release

## Update ApprovalTests.cpp

Preparation:

- [ ] Push all changes
- [ ] Check that the [builds are passing](https://github.com/approvals/ApprovalTests.cpp/commits/master)
- [ ] Write in [build/relnotes_X.X.X.md](https://github.com/approvals/ApprovalTests.cpp/blob/master/build/relnotes_X.X.X.md) a  summary of changes since last release, based on changes since [the last release](https://github.com/approvals/ApprovalTests.cpp/releases)
- [ ] Determine the semantic version number
- [ ] Update the version number in [build_hpp.sh](/build/build_hpp.sh)
- [ ] On the features page, add the line `## [new version number]` after `## vNext`

Creating the Build

- [ ] Run `build_hpp.sh` - this updates [the starter project](https://github.com/approvals/ApprovalTests.cpp.StarterProject), tests that it builds, and if so, **commits and pushes it**

Publishing

- [ ] Commit and push `ApprovalTests.cpp`
- [ ] Finish off the upload to github, by uploading the new .hpp, pasting in the release notes, and hitting "Publish release"
- [ ] Finish off the release Tweet
- [ ] Close any [Issues](https://github.com/approvals/ApprovalTests.cpp/issues) that were resolved in this release

Prepare for next release

- [ ] Change version number to current version number, and new version number to `$UNSET_VERSION`
- [ ] Make sure the release notes named with the new version exist
- [ ] `cp relnotes_template.md relnotes_X.X.X.md`
