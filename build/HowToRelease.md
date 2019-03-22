<a id="top"></a>
# How To Release

## Update ApprovalTests.cpp

Preparation:

* Check that the builds are passing: https://github.com/approvals/ApprovalTests.cpp/commits/master
* Write summary of changes since last release, based on changes since last release: https://github.com/approvals/ApprovalTests.cpp/releases
* Determine the semantic version number
* Update the version number in `build_hpp.sh`

Creating the build

* Run `build_hpp.sh` - this updates the starter project and tests that it builds

Publishing
 
* Upload the .hpp to releases - call the release `Single Hpp File`
* Change the version numbers in `build_hpp.sh` to reflect the next version
* Commit and push `ApprovalTests.cpp`
* Finish off the release Tweet