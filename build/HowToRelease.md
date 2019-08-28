<a id="top"></a>
# How To Release

## Update ApprovalTests.cpp

Preparation:

- [ ] Push all changes
- [ ] Check that the [builds are passing](https://github.com/approvals/ApprovalTests.cpp/commits/master)
- [ ] Write summary of changes since last release, based on changes since [the last release](https://github.com/approvals/ApprovalTests.cpp/releases)
- [ ] Determine the semantic version number
- [ ] Update the version number in [build_hpp.sh](/build/build_hpp.sh)

Creating the build

- [ ] Run `build_hpp.sh` - this updates [the starter project](https://github.com/approvals/ApprovalTests.cpp.StarterProject), tests that it builds, and if so, **commits and pushes it**

Publishing

- [ ] Change version number to current version number, and new version number to `$UNSET_VERSION`
- [ ] Commit and push `ApprovalTests.cpp`
- [ ] Finish off the upload to github, by uploading the new .hpp, pasting in the release notes, and hitting "Publish release"
- [ ] Finish off the release Tweet
- [ ] Close any Issues that were resolved in this release

Prepare for next repease

- [ ] Clone relnotes_template.md to relnotes_X.X.X.md
